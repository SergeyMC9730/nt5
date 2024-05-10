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

typedef struct rsb_array_Event rsb_array_Event;

#include <nt5emul/dwm/font.h>

struct dwm_context_fonts {
    struct dwm_context_font fonts[512];
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

    Vector2 size;

    rsb_array_Event *window_create_event;
    rsb_array_Event *window_close_event;
};

// draw dwm context
void _ntDwmDrawContext(struct dwm_context *ctx);

// create dwm context
struct dwm_context *_ntDwmCreateContext(const char *theme_path);
// executed in main thread
void _ntCreateDwmContextMain(struct dwm_context *ctx);

// load sounds from the dwm context
void _ntDwmLoadSounds(struct dwm_context *ctx);

// destroy dwm context
void _ntDwmDestroyContext(struct dwm_context *ctx);

// push window to the dwm context
// returns process id
int _ntDwmPushWindow(struct dwm_context *ctx, struct dwm_window wnd); 

// get dwm process ids
rsb_array_Int *_ntDwmGetProcesses(struct dwm_context *ctx);

// get dwm process ids (not for drawing)
rsb_array_Int *_ntDwmGetProcesses1(struct dwm_context *ctx);

// get raw list of dwm process ids
rsb_array_Int *_ntDwmGetProcessesRaw(struct dwm_context *ctx);

// get process by process id
struct dwm_window *_ntDwmGetProcess(struct dwm_context *ctx, int pid);

// global dwm
void _ntDwmSetGlobal(struct dwm_context *ctx);
// global dwm
struct dwm_context *_ntDwmGetGlobal();

// get local mouse position inside the dwm context
Vector2 _ntDwmGetLocalMousePosition(struct dwm_context *ctx);

// draw with loaded font
void _ntDwmDrawWithFont(struct dwm_context *ctx, Vector2 pos, Color col, const char *text, const char *font_name);

// load font into the dwm context
void _ntDwmLoadFont(struct dwm_context *ctx, int xsz, float sp, const char *path, const char *name);

// get loaded font
struct dwm_context_font _ntDwmGetFont(struct dwm_context *ctx, const char *name);

// set size for this dwm instance
void _ntDwmSetSize(struct dwm_context *ctx, Vector2 size);

// get size for this dwm instance
Vector2 _ntDwmGetSize(struct dwm_context *ctx);