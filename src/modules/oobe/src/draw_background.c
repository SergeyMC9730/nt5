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

#include <nt5emul/ntcore.h>

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

int current_bar = 0;

void setup_process_bars() {
    int bars_length = sizeof(bars) / sizeof(struct auto_progress_bar);

    struct auto_progress_bar *bar = bars + current_bar;

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
        ((current_bar + 1) < bars_length)
    ) {
        current_bar++;
    }
}

void draw_background(void *ctx) {
    if (_state.old_draw != NULL) _state.old_draw(_state.old_ctx);

    oobe_steps[0].name = _state.cterm_setup_colinfo;
    oobe_steps[1].name = _state.cterm_setup_dynupd;
    oobe_steps[2].name = _state.cterm_setup_prepinst;
    oobe_steps[3].name = _state.cterm_setup_instwin;
    oobe_steps[4].name = _state.cterm_setup_final;

    DrawText("AAAAAAA", 50, 50, 32, WHITE);

    Vector2 sz = {
        .x = GetRenderWidth(),
        .y = GetRenderHeight()
    };

    // main background

    _ntModOobeDrawStretchedTexture(_state.main_bg_texture, true, true, 1.f, 1.f, (Vector2){}, (Vector2){}); 

    // status background

    float bg_y_mul = sz.y / (float)_state.main_bg_texture.height;

    Vector2 bg_sz = {
        (float)_state.main_bg_texture.width,
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

    float c3 = _ntGetMiddleValue(bg_sz.x * 2.f, sz.x) - 140;

    Vector2 bg1_pos = {
       c3, c1
    };
    Vector2 bg1_pos2 = {
       bg1_pos.x, c2
    };

    _ntModOobeDrawSizedTexture(_state.main_bg_texture, (Vector2){1.f, 1.f}, bg1_pos, (Vector2){});
    _ntModOobeDrawSizedTexture(_state.main_bg_texture, (Vector2){1.f, -1.f}, bg1_pos2, (Vector2){});

    _state.main_bg_texture.width = bg_old_sz.x;
    _state.main_bg_texture.height = bg_old_sz.y;

    Vector2 line_btm = {
        .x = 0,
        .y = sz.y - (_state.line_bottom_texture.height * 0.7f) + 4
    };
    Vector2 line_top = {
        .x = 0,
        .y = -(_state.line_top_texture.height * 0.33f) 
    };

    // draw lines
    _ntModOobeDrawStretchedTexture(_state.line_bottom_texture, true, false, 1.f, 1.f, line_btm, (Vector2){}); 
    _ntModOobeDrawStretchedTexture(_state.line_top_texture, true, false, 1.f, 1.f, line_top, (Vector2){});

    // draw logo    
    DrawTextureEx(_state.logo_texture, (Vector2){10, 2}, 0.f, 0.7f, WHITE);

    // draw steps
    int sl = _ntModOobeDrawSteps(oobe_steps, sizeof(oobe_steps) / sizeof(struct oobe_install_step)); 

    // draw completion time

    // get bold tahoma font from the DWM
    struct dwm_context_font font = _state.dwm_ctx->fonts.tahoma9_bld;

    // calculate text position based on the steps length
    Vector2 text_pos = {
        26,
        sl
    };

    // draw completion text
    DrawTextEx(
        font.font, // font
        TextFormat(_state.cterm_setup_time_approx, _state.minutes_left), // formatted string
        text_pos, // pos
        font.real_size, // size in pixels
        font.spacing, // spacing
        WHITE // color
    );

    // draw description

    // check if F2 key is pressed
	if (IsKeyPressed(KEY_F2)) {
		// dump core information
        _ntDumpCores();
	}

    setup_process_bars();
}