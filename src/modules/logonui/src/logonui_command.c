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

#include <nt5emul/modules/logonui/logonui_command.h>
#include <nt5emul/modules/logonui/state.h>
#include <nt5emul/middle.h>

#include <nt5emul/renderer.h>

#include <nt5emul/timer.h>

#include <unistd.h>

#include <nt5emul/nt_config.h>

#include <stdio.h>

void logonui_exit(void *ctx) {
    // get renderer state
    renderer_state_t *st = _ntRendererGetState();

    int layer_index = 0;
    // get layer at index 0
    renderer_layer_t *layer = st->layers + layer_index;

    // recover old layer
    *layer = _state.old_layer;

    // creating texture list as pointers to save stack space
    Texture2D *textures[] = {
        &_state.line_bottom_texture, &_state.line_top_texture,
    };

    // get array size
    size_t sz = sizeof(textures) / sizeof(Texture2D *);

    for (size_t i = 0; i < sz; i++) {
        // unload each texture
        UnloadTexture(textures[i][0]);
    }

    // const char *config_path = "nt/config.json";

    // // read config
    // struct nt_config config = _ntGetConfig(config_path);

    _state.execution_lock = false;
}

void draw_background(void *ctx) {
    if (_state.old_layer.on_draw.callback != NULL) _state.old_layer.on_draw.callback(_state.old_layer.on_draw.user);

    renderer_state_t *st = _ntRendererGetState();

    Vector2 sz = {
        .x = st->current_window_size.x,
        .y = st->current_window_size.y
    };

    Vector2 line_btm = {
        .x = 0,
        .y = sz.y - _state.line_bottom_texture.height
    };
    Vector2 line_top = {
        .x = 0,
        .y = 0
    };

    // main background

    _ntRendererDrawStretchedTexture(_state.main_bg_texture, true, true, 1.f, 1.f, (Vector2){}, (Vector2){}); 

    // draw lines
    _ntRendererDrawStretchedTexture(_state.line_bottom_texture, true, false, 1.f, 1.f * st->scaling, line_btm, (Vector2){}); 
    _ntRendererDrawStretchedTexture(_state.line_top_texture, true, false, 1.f, 1.f * st->scaling, line_top, (Vector2){});

    // get franklin font from the DWM
    struct dwm_context_font font = _ntDwmGetFont(_state.dwm_ctx, "framd24");

    // calculate text size
    Vector2 text_sz = MeasureTextEx(font.font, _state.cterm_logonui_welcome, font.real_size, font.spacing);

    // text position
    Vector2 text_pos = {
        _ntGetMiddleValue(text_sz.x, st->current_window_size.x) * 1.3f,
        _ntGetMiddleValue(text_sz.y, st->current_window_size.y)
    };

    Color shadow = {
        // 003399
        .r = 0x00,
        .g = 0x33,
        .b = 0x99
    };
    shadow.a = 256 * 0.75f;

    // draw welcome text
    // draw shadow first
    DrawTextEx(
        font.font,      // font
                        // string
        _state.cterm_logonui_welcome,
        text_pos,       // pos
        font.real_size, // size in pixels
        font.spacing,   // spacing
        shadow          // color
    );

    text_pos.x -= (3 * st->scaling);
    text_pos.y -= (3 * st->scaling);

    // draw the text itself
    DrawTextEx(
        font.font,      // font
                        // string
        _state.cterm_logonui_welcome,
        text_pos,       // pos
        font.real_size, // size in pixels
        font.spacing,   // spacing
        WHITE           // color
    );
}

void logonui_preload(void *ctx) {
    _state.main_bg_texture = LoadTexture("nt/images/user/ui/newmark1.jpg");
    _state.line_bottom_texture = LoadTexture("nt/images/user/ui/newbtm1.jpg");
    _state.line_top_texture = LoadTexture("nt/images/user/ui/newtop1.jpg");

    SetWindowState(FLAG_WINDOW_RESIZABLE);
}

#include <nt5emul/timer.h>

void logonui_exit_queue(void *ctx) {
    // unload all textures on the next frame and recover old layer parameters
    _ntRendererPushQueue(logonui_exit, NULL);
}

bool logonui_command(void *data) {
    if (_state.execution_lock) {
        printf("error: only a single logonui process can be run at the same time\n");

        return false;
    }

    _state.execution_lock = true;

    // get renderer state
    renderer_state_t *st = _ntRendererGetState();

    int layer_index = 0;

    // get layer pointer at index of 0
    renderer_layer_t *layer = st->layers + layer_index;

    // save old layer
    _state.old_layer = *layer;

    // period count
    int times = 2;
    // how long each period would be
    int mul = 3;

    layer->on_draw.callback = draw_background;

    // load all textures before rendering oobe layer
    _ntRendererPushQueue(logonui_preload, NULL);

    struct nt_config cfg = _ntGetConfig("nt/config.json");

    const char *lang = cfg.selected_lang;

    // free config
    _ntUnloadConfig(cfg);

    // get global dwm context
    _state.dwm_ctx = _ntDwmGetGlobal();

    _state.cterm_logonui_welcome = _ntGetStringInLanguagePack( _state.dwm_ctx->lpack, "cterm_logonui_welcome", lang);

    _ntSetupTimerSync(1.5);

    logonui_exit_queue(NULL);

    return true;
}