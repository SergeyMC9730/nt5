/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  Sergei Baigerov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact Sergei Baigerov -- @dogotrigger in Discord
*/

#include <nt5emul/modules/notify/notify_command.h>
#include <nt5emul/modules/notify/state.h>
#include <nt5emul/renderer.h>
#include <nt5emul/arrays/rsb_array_char.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void notify_draw(void *data) {
    float step = GetFrameTime() / 2.f;

    if (_state.old_draw) _state.old_draw(_state.old_ctx);
    
    if (_state.opacity >= 0.f) _state.opacity -= step;
    else {
        free((void *)_state.message);

        renderer_state_t *st = _ntRendererGetState();
        renderer_layer_t *layer = st->layers + RENDERER_LAYERS - 1;

        layer->draw = _state.old_draw;
        layer->user = _state.old_ctx;

        _state.opacity = 1.f;
        _state.running = false;

        st->draw_fps = _state.old_show_fps;

        return;
    }

    Color c = WHITE;
    Color c2 = BLACK;

    c.a *= _state.opacity;
    c2.a *= _state.opacity;

    DrawTextEx(_state.font, _state.message, (Vector2){4,4}, 20, 0.5f, c2);
    DrawTextEx(_state.font, _state.message, (Vector2){3,3}, 20, 0.5f, c);
}

void notify_scheduled(void *ctx) {
    if (_state.font.recs != NULL) return;
    
    _state.font = LoadFontEx("ntresources/SpaceMono-Regular.ttf", 20.f, NULL, 0);
}

bool notify_command(void *data) {
    const char **strs = (const char **)data;
    const char *msg = strs[1];

    bool update_message_only = _state.running;

    if (!msg) {
        printf("error: message should be provided\n");

        return false;
    }

    _state.running = true;
    _state.opacity = 1.f;

    size_t sz = sizeof(char *) * 256 + 1;

    if (!update_message_only) {
        _state.message = (const char *)malloc(sz);
    
        if (_ntRendererInThread()) notify_scheduled(NULL);
        else {
            _ntRendererPushQueue(notify_scheduled, NULL);
        }

        while (_state.font.recs == NULL) {
            usleep(10000);
        }
    }

    Vector2 rsz = {
        GetRenderWidth(),
        GetRenderHeight()
    };

    rsb_array_String *str_array = RSBCreateArrayString();

    Vector2 base_text_pos = {3, 3};
    Vector2 current_text_pos = base_text_pos;

    memset((void *)_state.message, 0, sz);

    for (int i = 0; i < 255; i++) {
        const char *msg2 = strs[1 + i];

        if (msg2 == NULL) break;

        if (i != 0) strcat((char *)_state.message, " ");
        strcat((char *)_state.message, msg2);
    }

    for (int i = 0; i < strlen(_state.message); i++) {
        char c = _state.message[i];
        const char cs[] = {c, 0};

        Vector2 csize = MeasureTextEx(_state.font, cs, 20, 0.5f);
        
        current_text_pos.x += csize.x + 1.f;

        // printf("i=%d; c=%c; x=%f\n", i, c, current_text_pos.x);

        if (current_text_pos.x > rsz.x) {
            current_text_pos.x = base_text_pos.x;

            RSBAddElementString(str_array, '\n');

            // printf("newline has been placed on %c (%d)\n", c, i);
        }

        RSBAddElementString(str_array, c);
    }

    RSBAddElementString(str_array, 0);

    memset((void *)_state.message, 0, sz);
    strncpy((char *)_state.message, str_array->objects, sz - 1);

    RSBDestroyString(str_array);

    if (!update_message_only) {
        renderer_state_t *st = _ntRendererGetState();
        renderer_layer_t *layer = st->layers + RENDERER_LAYERS - 1;

        _state.old_draw = layer->draw;
        _state.old_ctx = layer->user;

        layer->draw = notify_draw;

        _state.old_show_fps = st->draw_fps;
        st->draw_fps = false;
    }

    return true;
}