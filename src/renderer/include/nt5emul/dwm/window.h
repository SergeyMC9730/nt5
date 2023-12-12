#pragma once

#include <raylib.h>

struct dwm_window_bool {
    bool state;
    bool ability;
};

struct dwm_window {
    Vector2 position;
    Vector2 size;
    
    const char *title;

    struct dwm_window_bool closed;
    struct dwm_window_bool hidden;
    struct dwm_window_bool filled;

    void (*draw)(struct dwm_window *wnd, void *ctx);
    void (*upadte)(struct dwm_window *wnd, void *ctx);
};

struct dwm_window _ntCreateWindow(const char *title, Vector2 size);
void _ntDrawWindow(struct dwm_window *wnd, void *ctx);