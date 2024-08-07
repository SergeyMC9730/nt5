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

#include <nt5emul/modules/oobe/state.h>
#include <nt5emul/modules/oobe/render.h>
#include <nt5emul/middle.h>
#include <nt5emul/renderer.h>
#include <nt5emul/modules/oobe/oobe_install_step.h>
#include <nt5emul/ntcore.h>
#include <nt5emul/dwm/context.h>

#ifndef NULL
#define NULL (void *)0
#endif

struct oobe_install_step oobe_steps[] = {
    {"Collecting\ninformation", true}, 
    {"Dynamic\nUpdate", true}, 
    {"Preparing\ninstallation", true},
    {"Installing\nWindows", false, true}, 
    {"Finalizing\ninstallation", false, false}
};

#include <nt5emul/modules/oobe/auto_progress_bar.h>

struct auto_progress_bar bars[] = {
    {
        .speed = 1.f,
        .title = "Installing Devices"
    },
    {
        .speed = 1.f,
        .title = "Installing Network"
    },
    {
        .speed = 0.5f,
        .title = "Copying files..."
    },
    {
        .speed = 1.f,
        .title = "Completing installation..."
    },
    {
        .speed = 2.f,
        .title = "Installing Start menu items"
    },
    {
        .speed = 0.5f,
        .title = "Registering components"
    },
    {
        .speed = 4.f,
        .title = "Saving settings"
    }
};

void setup_process_bars() {
    int bars_length = sizeof(bars) / sizeof(struct auto_progress_bar);

    struct auto_progress_bar *bar = bars + _state.current_bar;

    bars[0].title = _state.cterm_setup_installing_devices;
    bars[1].title = _state.cterm_setup_installing_network;
    bars[2].title = _state.cterm_setup_copying_files;
    bars[3].title = _state.cterm_setup_completing_install;
    bars[4].title = _state.cterm_setup_installing_start;
    bars[5].title = _state.cterm_setup_registering_components;
    bars[6].title = _state.cterm_setup_saving_settings;

    _ntModOobeUpdateAPB(bar);
    _ntModOobeDrawAPB(*bar);

    if (
        bar->progress >= 1.f && 
        ((_state.current_bar + 1) < bars_length)
    ) {
        _state.current_bar++;
    }
}

void setup_reset_bars() {
    int bars_length = sizeof(bars) / sizeof(struct auto_progress_bar);

    for (int i = 0; i < bars_length; i++) {
        bars[i].progress = 0.f;
    }
}

struct xp_feature {
    const char *name;
    const char *description;
};

struct xp_feature _features[5] = {};
bool _features_loaded = false;

void draw_xp_features() {
    Vector2 title_pos = {
        
    };
}

void draw_background(void *ctx) {
    if (!_features_loaded) {
        _features[0].name = "An exciting new look";
        _features[0].description = "123";
    }

    if (_state.old_layer.on_draw.callback) _state.old_layer.on_draw.callback(_state.old_layer.on_draw.user);

    oobe_steps[0].name = _state.cterm_setup_colinfo;
    oobe_steps[1].name = _state.cterm_setup_dynupd;
    oobe_steps[2].name = _state.cterm_setup_prepinst;
    oobe_steps[3].name = _state.cterm_setup_instwin;
    oobe_steps[4].name = _state.cterm_setup_final;

    renderer_state_t *st = _ntRendererGetState();

    DrawText("AAAAAAA", 50 * st->scaling, 50 * st->scaling, 32 * st->scaling, WHITE);

    Vector2 sz = {
        .x = st->current_window_size.x,
        .y = st->current_window_size.y
    };

    // main background

    _ntRendererDrawStretchedTexture(_state.main_bg_texture, true, true, 1.f, 1.f, (Vector2){}, (Vector2){}); 

    // status background

    float bg_y_mul = sz.y / (float)_state.main_bg_texture.height * st->scaling;

    Vector2 bg_sz = {
        (float)_state.main_bg_texture.width * st->scaling,
        (float)_state.main_bg_texture.height * bg_y_mul
    };
    Vector2 bg_old_sz = {
        _state.main_bg_texture.width,
        _state.main_bg_texture.height
    };

    _state.main_bg_texture.width = bg_sz.x;
    _state.main_bg_texture.height = bg_sz.y;

    float c1 = _ntGetMiddleValue(bg_sz.y * 2.f, sz.y);
    float c2 = _ntGetMiddleValue(bg_sz.y, sz.y * 2.f);

    float c3 = _ntGetMiddleValue(bg_sz.x * 2.f, sz.x) - (140 * st->scaling);

    Vector2 bg1_pos = {
       c3, c1
    };
    Vector2 bg1_pos2 = {
       bg1_pos.x, c2
    };

    _ntRendererDrawSizedTexture(_state.main_bg_texture, (Vector2){1.f * st->scaling, 1.f * st->scaling}, bg1_pos, (Vector2){}, true);
    _ntRendererDrawSizedTexture(_state.main_bg_texture, (Vector2){1.f * st->scaling, -1.f * st->scaling}, bg1_pos2, (Vector2){}, true);

    _state.main_bg_texture.width = bg_old_sz.x;
    _state.main_bg_texture.height = bg_old_sz.y;

    // process lines

    float logo_y = (float)_state.logo_texture.height * st->scaling;

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
    DrawTextureEx(_state.logo_texture, (Vector2){10 * st->scaling, 2 * st->scaling}, 0.f, 0.7f * st->scaling, WHITE);

    // draw steps
    int sl = _ntModOobeDrawSteps(oobe_steps, sizeof(oobe_steps) / sizeof(struct oobe_install_step)); 

    // draw completion time

    // get bold tahoma font from the DWM
    struct dwm_context_font font = _ntDwmGetFont(_state.dwm_ctx, "tahomabd9");

    // text position based on the steps length
    Vector2 text_pos = {
        26 * st->scaling, // x
        sl  // y
    };

    // draw completion text
    DrawTextEx(
        font.font,      // font
                        // formatted string
        TextFormat(_state.cterm_setup_time_approx, _state.minutes_left),
        text_pos,       // pos
        font.real_size, // size in pixels
        font.spacing,   // spacing
        WHITE           // color
    );

    // draw description
    // not implemented lol

    // check if F2 key is pressed
	if (IsKeyPressed(KEY_F2)) {
		// dump core information
        _ntDumpCores();
	}
    
    // draw progress bar
    setup_process_bars();

    // draw xp features
    draw_xp_features();
}