#pragma once

#include "theme.h"
#include "window.h"

#include <nt5emul/arrays/rsb_array_gen.h>

RSB_ARRAY_DEF_GEN(struct dwm_window, DWMWindow);

struct dwm_context {
    struct dwm_theme theme;

    rsb_array_DWMWindow *windows;
    struct dwm_window *selected_window;
};

// draw dwm context
void _ntDrawDwmContext(struct dwm_context *ctx);

// create dwm context
struct dwm_context *_ntCreateDwmContext(const char *theme_path);

// destroy dwm context
void _ntDestroyDwmContext(struct dwm_context *ctx);

// push window to the dwm context
void _ntPushWindow(struct dwm_context *ctx, struct dwm_window wnd);