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
#include <nt5emul/middle.h>

#include <nt5emul/nt_config.h>

#include <nt5emul/dwm/button.h>

void msoobe_new() {
    _ntRendererSetFPS(_state.old_fps);

    _ntDwmUnloadVideo(_state.xp_vid);
    UnloadTexture(_state.xp_vid.texture);

    _state.xp_vid.texture.width = 0;
    _state.xp_vid.stream = NULL;

    setup_preload(NULL);

    // get renderer state
    renderer_state_t *st = _ntRendererGetState();

    _ntRendererSetWindowSize((Vector2){800 * st->scaling, 600 * st->scaling});

    st->draw_fps = true;
}

extern void setup_exit(void *ctx);

void msoobe_exit() {
    setup_exit(NULL);

    const char *config_path = "nt/config.json";

    struct nt_config config = _ntGetConfig(config_path);
    config.oobe_completed = true;

    // check if no users were been created
    bool user_created = false;
    for (int i = 0; i < NT_MAX_USERS; i++) {
        if (user_created) break;

        user_created = config.user[i].created;
    }

    if (!user_created) {
        // create user
        _ntAddUserToConfig(&config, "Administrator");
    }

    // save config
    _ntSaveConfig(config, config_path);

    // free config
    _ntUnloadConfig(config);
}

#include <sys/stat.h>

void msoobe_setup_user_profile() {
    mkdir("nt/profile", 0777);
}

void msoobe_draw(void *ctx) {
    _ntRendererDrawStretchedTexture(_state.main_bg_texture, true, true, 1.f, 1.f, (Vector2){}, (Vector2){});

    // get renderer state
    renderer_state_t *st = _ntRendererGetState();

    Vector2 sz = {
        .x = st->current_window_size.x,
        .y = st->current_window_size.y
    };

    // process lines

    float logo_y = (float)_state.logo_texture.height * st->scaling + (10 * st->scaling);

    Vector2 line_btm = {
        .x = 0,
        .y = sz.y - logo_y
    };
    Vector2 line_top = {
        .x = 0,
        .y = -(float)(_state.line_top_texture.height * st->scaling) + logo_y
    };

    float x_mul = sz.x / (float)_state.line_bottom_texture.width;

    // draw lines

    _ntRendererDrawSizedTexture(_state.line_bottom_texture, (Vector2){x_mul, 1.f * st->scaling}, line_btm, (Vector2){}, false);

    x_mul = sz.x / (float)_state.line_top_texture.width;
    _ntRendererDrawSizedTexture(_state.line_top_texture, (Vector2){x_mul, 1.f * st->scaling}, line_top, (Vector2){}, false);

    // draw logo    
    DrawTextureEx(_state.logo_texture, (Vector2){20 * st->scaling, 5 * st->scaling}, 0.f, 1.f * st->scaling, WHITE);
    
    struct dwm_context_font big_font = _ntDwmGetFont(_state.dwm_ctx, "framd24");
    struct dwm_context_font small_font = _ntDwmGetFont(_state.dwm_ctx, "tahoma9");
    struct dwm_context_font small_fontar = _ntDwmGetFont(_state.dwm_ctx, "arial9");

    Color shadow = {
        // 003399
        .r = 0x00,
        .g = 0x33,
        .b = 0x99
    };
    shadow.a = 256 * 0.75f;

    Vector2 big_text_base_pos = {
        63 * st->scaling, 66 * st->scaling
    };

    // Draw text
    DrawTextEx(big_font.font, _state.cterm_msoobe_welcome, (Vector2){big_text_base_pos.x + (3 * st->scaling), big_text_base_pos.y + (3 * st->scaling)},  big_font.real_size, big_font.spacing, shadow);
    DrawTextEx(big_font.font, _state.cterm_msoobe_welcome, big_text_base_pos,  big_font.real_size, big_font.spacing, WHITE);

    DrawTextEx(small_font.font, _state.cterm_msoobe_incomplete, (Vector2){big_text_base_pos.x, (131 * st->scaling)}, small_font.real_size, small_font.spacing, WHITE);

    DrawTextEx(small_fontar.font, _state.cterm_msoobe_enter_continue, (Vector2){(17 * st->scaling), sz.y - _state.line_top_texture.height - (75 * st->scaling)}, small_fontar.real_size, small_fontar.spacing, WHITE);

    struct dwm_button btn_next = {
        .activated.ability = true,
        .howered.ability = true,
        .off = _state.square_next_texture_off,
        .on = _state.square_next_texture_on,
        .button.width = _state.square_next_texture_off.width * st->scaling,
        .button.height = _state.square_next_texture_off.height * st->scaling,
        .button.x = st->current_window_size.x - (((24.f * st->scaling) + (_state.square_next_texture_off.width * st->scaling))),
        .button.y = st->current_window_size.y - (((14.f * st->scaling) + (_state.square_next_texture_off.height * st->scaling)))
    };

    Vector2 btn_next_text_sz = MeasureTextEx(small_fontar.font, _state.cterm_msoobe_next, small_fontar.real_size, small_fontar.spacing);
    int btn_next_text_yal = _ntGetMiddleValue(btn_next_text_sz.y, btn_next.button.height);

    Vector2 btn_next_text = {
        btn_next.button.x - (4 * st->scaling) - btn_next_text_sz.x,
        btn_next.button.y + btn_next_text_yal
    };

    DrawTextEx(small_fontar.font, _state.cterm_msoobe_next, btn_next_text, small_fontar.real_size, small_fontar.spacing, WHITE);
    _ntDrawDWMButton(_state.dwm_ctx, &btn_next);

    struct dwm_button btn_skip = {
        .activated.ability = true,
        .howered.ability = true,
        .off = _state.square_skip_texture_off,
        .on = _state.square_skip_texture_on,
        .button.width = _state.square_skip_texture_off.width * st->scaling,
        .button.height = _state.square_skip_texture_off.height * st->scaling,
        .button.x = btn_next_text.x - _state.square_skip_texture_off.width - (24 * st->scaling),
        .button.y = btn_next.button.y
    };

    Vector2 btn_skip_text_sz = MeasureTextEx(small_fontar.font, _state.cterm_msoobe_skip, small_fontar.real_size, small_fontar.spacing);
    int btn_skip_text_yal = _ntGetMiddleValue(btn_skip_text_sz.y, btn_skip.button.height);

    Vector2 btn_skip_text = {
        btn_skip.button.x - (4 * st->scaling) - btn_skip_text_sz.x,
        btn_skip.button.y + btn_skip_text_yal
    };

    DrawTextEx(small_fontar.font, _state.cterm_msoobe_skip, btn_skip_text, small_fontar.real_size, small_fontar.spacing, WHITE);
    if (_ntDrawDWMButton(_state.dwm_ctx, &btn_skip) && _state.xp_vid.texture.width == 0) {
        msoobe_exit();
    }

    if (_state.xp_vid.texture.width != 0) _ntRendererDrawStretchedTexture(_state.xp_vid.texture, true, true, 1.f, 1.f, (Vector2){0, 0}, (Vector2){0, 0});
}
void msoobe_update(void *ctx) {
    if (_state.frame_1 == 0) {
        // TEMP
        _state.old_fps = GetMonitorRefreshRate(0);
    }

    _ntDwmUpdateVideo(_state.xp_vid);

    if (_state.frame_1 != -1) {
        _state.frame_2 = _state.frame_1;
        _state.frame_1 = _state.xp_vid.stream->codecContext->frame_num;
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

    SetTextureFilter(_state.xp_vid.texture, TEXTURE_FILTER_BILINEAR);

    _ntRendererSetFPS(15);

    renderer_state_t *st  = _ntRendererGetState();

    _ntRendererSetWindowSize((Vector2){800 * st->scaling, 600 * st->scaling});
}

bool msoobe_command(struct cterm_command *data) {
    if (_state.execution_lock) {
        printf("error: only a single msoobe process can be run at the same time\n");

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

    // get global dwm context
    _state.dwm_ctx = _ntDwmGetGlobal();

    layer->on_draw.callback = msoobe_draw;
    layer->on_update.callback = msoobe_update;

    // load all textures before rendering oobe layer
    _ntRendererPushQueue(msoobe_preload, NULL);

    _state.music_title = LoadSound("nt/sounds/title.mp3");

    PlaySound(_state.music_title);

    _ntDwmLoadSounds(_state.dwm_ctx);

    struct nt_config cfg = _ntGetConfig("nt/config.json");

    const char *lang = cfg.selected_lang;

    // free config
    _ntUnloadConfig(cfg);

    _state.frame_1 = 0;
    _state.frame_2 = _state.frame_1;

    _state.cterm_msoobe_welcome = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_msoobe_welcome", lang);
    _state.cterm_msoobe_incomplete = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_msoobe_incomplete", lang);
    _state.cterm_msoobe_enter_continue = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_msoobe_enter_continue", lang);
    _state.cterm_msoobe_next = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_msoobe_next", lang);
    _state.cterm_msoobe_skip = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_msoobe_skip", lang);

    return true;
}