#pragma once

#include "theme.h"
#include "window.h"

#include <nt5emul/arrays/rsb_array_gen.h>

RSB_ARRAY_DEF_GEN(struct dwm_window, DWMWindow);

struct dwm_context_font {
    Font font;
    int xp_size;
    int real_size;
};

struct dwm_context_fonts {
    struct dwm_context_font tahoma8_std;
    struct dwm_context_font tahoma8_bld;
};

struct dwm_context {
    struct dwm_theme theme;

    rsb_array_DWMWindow *windows;
    struct dwm_window *selected_window;

    struct dwm_context_fonts fonts;

    bool loading_finished;

    int global_process_increment;
};

// draw dwm context
void _ntDrawDwmContext(struct dwm_context *ctx);

// create dwm context
struct dwm_context *_ntCreateDwmContext(const char *theme_path);
// executed in main thread
void _ntCreateDwmContextMain(struct dwm_context *ctx);

// destroy dwm context
void _ntDestroyDwmContext(struct dwm_context *ctx);

// push window to the dwm context
void _ntPushWindow(struct dwm_context *ctx, struct dwm_window wnd);

// get dwm process ids
rsb_array_Int *_ntGetDWMProcesses(struct dwm_context *ctx);

// get process by process id
struct dwm_window *_ntGetDWMProcess(struct dwm_context *ctx, int pid);