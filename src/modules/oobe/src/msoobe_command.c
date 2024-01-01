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

#include <nt5emul/modules/oobe/msoobe_command.h>
#include <nt5emul/modules/oobe/state.h>

#include <nt5emul/modules/oobe/render.h>

#include <nt5emul/renderer.h>

#include <nt5emul/timer.h>

#include <nt5emul/nt_config.h>

void msoobe_new() {
    SetTargetFPS(_state.old_fps);

    _ntDwmUnloadVideo(_state.xp_vid);
    UnloadTexture(_state.xp_vid.texture);

    _state.xp_vid.texture.width = 0;
    _state.xp_vid.stream = NULL;

    setup_preload(NULL);
}

void msoobe_draw(void *ctx) {
    _ntModOobeDrawStretchedTexture(_state.main_bg_texture, true, true, 1.f, 1.f, (Vector2){}, (Vector2){});

    Vector2 sz = {
        .x = GetRenderWidth(),
        .y = GetRenderHeight()
    };

    Vector2 line_btm = {
        .x = 0,
        .y = sz.y - (_state.line_bottom_texture.height)
    };
    Vector2 line_top = {
        .x = 0,
        .y = 0
    };

    // draw lines
    _ntModOobeDrawStretchedTexture(_state.line_bottom_texture, true, false, 1.f, 1.f, line_btm, (Vector2){}); 
    _ntModOobeDrawStretchedTexture(_state.line_top_texture, true, false, 1.f, 1.f, line_top, (Vector2){});

    // draw logo    
    DrawTextureEx(_state.logo_texture, (Vector2){15, 6}, 0.f, 1.f, WHITE);
    
    struct dwm_context_font big_font = _state.dwm_ctx->fonts.franklin24_bld;
    struct dwm_context_font small_font = _state.dwm_ctx->fonts.tahoma9_std;

    Color shadow = {
        // 003399
        .r = 0x00,
        .g = 0x33,
        .b = 0x99
    };
    shadow.a = 256 * 0.75;

    // Draw text
    DrawTextEx(big_font.font, _state.cterm_msoobe_welcome, (Vector2){63 + 3, 75 + 3},  big_font.real_size, big_font.spacing, shadow);
    DrawTextEx(big_font.font, _state.cterm_msoobe_welcome, (Vector2){63, 75},  big_font.real_size, big_font.spacing, WHITE);

    DrawTextEx(small_font.font, _state.cterm_msoobe_incomplete, (Vector2){63, 131}, small_font.real_size, small_font.spacing, WHITE);

    if (_state.xp_vid.texture.width != 0) _ntModOobeDrawStretchedTexture(_state.xp_vid.texture, true, true, 1.f, 1.f, (Vector2){0, 0}, (Vector2){0, 0});
}
void msoobe_update(void *ctx) {

    _ntDwmUpdateVideo(_state.xp_vid);

    if (_state.frame_1 != -1) {
        _state.frame_2 = _state.frame_1;
        _state.frame_1 = _state.xp_vid.stream->codecContext->frame_number;
    }

    if (_state.frame_1 == _state.frame_2) {
        msoobe_new();
        _state.frame_1 = -1;
    }
}

void msoobe_recover_fps(void *ctx) {
    SetTargetFPS(_state.old_fps);
}

void msoobe_preload(void *ctx) {
    _state.xp_vid = _ntDwmLoadVideo("nt/videos/user/intro.wmv");
    _state.old_fps = (1.f / GetFrameTime()) + 1;

    SetTextureFilter(_state.xp_vid.texture, TEXTURE_FILTER_BILINEAR);

    SetTargetFPS(15);
}

bool msoobe_command(void *data) {
    // get renderer state
    renderer_state_t *st = _ntRendererGetState();

    int layer_index = 0;

    // get layer pointer at index of 0
    renderer_layer_t *layer = st->layers + layer_index;

    // save old layer
    _state.old_draw = layer->draw;
    _state.old_update = layer->update;
    _state.old_ctx = layer->user;

    // get dwm context from the user input
    _state.dwm_ctx = data;

    layer->draw = msoobe_draw;
    layer->update = msoobe_update;

    // load all textures before rendering oobe layer
    _ntRendererPushQueue(msoobe_preload, NULL);
    
    InitAudioDevice();

    _state.music_title = LoadSound("nt/sounds/title.mp3");

    PlaySound(_state.music_title);

    _ntDwmLoadSounds(_state.dwm_ctx);

    struct nt_config cfg = _ntGetConfig("nt/config.json");

    const char *lang = cfg.selected_lang;

    _state.cterm_msoobe_welcome = get_string("cterm_msoobe_welcome", lang);
    _state.cterm_msoobe_incomplete = get_string("cterm_msoobe_incomplete", lang);

    return true;
}