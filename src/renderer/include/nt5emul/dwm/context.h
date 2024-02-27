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

#pragma once

#include "theme.h"
#include "window.h"

#include <nt5emul/arrays/rsb_array_gen.h>

#include <nt5emul/language_pack.h>

RSB_ARRAY_DEF_GEN(struct dwm_window, DWMWindow);

#include <nt5emul/dwm/font.h>

struct dwm_context_fonts {
    struct dwm_context_font tahoma8_std;
    struct dwm_context_font tahoma8_bld;

    struct dwm_context_font tahoma9_bld;
    struct dwm_context_font tahoma9_std;

    struct dwm_context_font lucidacon10_std;

    struct dwm_context_font tahoma12_bld;
    struct dwm_context_font tahoma12_std;

    struct dwm_context_font franklin24_std;
    struct dwm_context_font franklin24_bld;

    struct dwm_context_font arial9_std;
};

struct dwm_context_sounds {
    Sound chimes;
    Sound chord;
    Sound ding;
    Sound xplogon;
    Sound xplogoff;
    Sound xpstartu;
    Sound xpshutdn;

    bool audio_device_initialized;
    bool sfx_loaded;
};

struct dwm_context {
    struct dwm_theme theme;

    rsb_array_DWMWindow *windows;
    struct dwm_window *selected_window;
    struct dwm_window *rendered_window;

    struct dwm_context_fonts fonts;
    struct dwm_context_sounds sounds;

    rsb_array_LanguagePackCell *lpack;

    bool loading_finished;

    int global_process_increment;
};

// draw dwm context
void _ntDrawDwmContext(struct dwm_context *ctx);

// create dwm context
struct dwm_context *_ntCreateDwmContext(const char *theme_path);
// executed in main thread
void _ntCreateDwmContextMain(struct dwm_context *ctx);

// load sounds from the dwm context
void _ntDwmLoadSounds(struct dwm_context *ctx);

// destroy dwm context
void _ntDestroyDwmContext(struct dwm_context *ctx);

// push window to the dwm context
// returns process id
int _ntPushWindow(struct dwm_context *ctx, struct dwm_window wnd); 

// get dwm process ids
rsb_array_Int *_ntGetDWMProcesses(struct dwm_context *ctx);

// get dwm process ids (not for drawing)
rsb_array_Int *_ntGetDWMProcesses1(struct dwm_context *ctx);

// get raw list of dwm process ids
rsb_array_Int *_ntGetDWMProcessesRaw(struct dwm_context *ctx);

// get process by process id
struct dwm_window *_ntGetDWMProcess(struct dwm_context *ctx, int pid);

// global dwm
void _ntDwmSetGlobal(struct dwm_context *ctx);
struct dwm_context *_ntDwmGetGlobal();

// get local mouse position inside the dwm context
Vector2 _ntDwmGetLocalMousePosition(struct dwm_context *ctx);