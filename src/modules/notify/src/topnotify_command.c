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

#include <nt5emul/modules/notify/topnotify_command.h>
#include <nt5emul/modules/notify/state.h>
#include <nt5emul/renderer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void topnotify_draw(void *data) {
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

        return;
    }

    Color c = WHITE;
    Color c2 = BLACK;

    c.a *= _state.opacity;
    c2.a *= _state.opacity;

    DrawText(_state.message, 4, 4, 20, c2);
    DrawText(_state.message, 3, 3, 20, c);
}

bool topnotify_command(void *data) {
    const char **strs = (const char **)data;
    const char *msg = strs[1];

    bool update_message_only = _state.running;

    if (!msg) {
        printf("error: message should be provided\n");

        return false;
    }

    _state.running = true;
    _state.opacity = 1.f;

    size_t sz = sizeof(char *) * 256;

    if (!update_message_only) {
        _state.message = (const char *)malloc(sz);
    }

    memset((void *)_state.message, 0, sz);

    for (int i = 0; i < 255; i++) {
        const char *msg2 = strs[1 + i];

        if (msg2 == NULL) break;

        if (i != 0) strcat((char *)_state.message, " ");
        strcat((char *)_state.message, msg2);
    }

    if (!update_message_only) {
        renderer_state_t *st = _ntRendererGetState();
        renderer_layer_t *layer = st->layers + RENDERER_LAYERS - 1;

        _state.old_draw = layer->draw;
        _state.old_ctx = layer->user;

        layer->draw = topnotify_draw;
    }

    return true;
}