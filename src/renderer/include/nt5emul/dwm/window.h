#pragma once

#include <raylib.h>

#include <nt5emul/arrays/rsb_array_int.h>

struct dwm_window_bool {
    bool state;
    bool ability;
};

struct dwm_process {
    int pid;
};

struct dwm_window {
    struct dwm_process process;

    Vector2 position;
    Vector2 size;

    Rectangle titlebar_rect;
    
    const char *title;

    struct dwm_window_bool closed;
    struct dwm_window_bool hidden;
    struct dwm_window_bool filled;
    struct dwm_window_bool moving;

    void (*draw)(struct dwm_window *wnd, void *ctx);
    void (*upadte)(struct dwm_window *wnd, void *ctx);
};

struct dwm_window _ntCreateWindow(const char *title, Vector2 size);

void _ntDrawWindow(struct dwm_window *wnd, void *ctx);
void _ntUpdateWindow(struct dwm_window *wnd, void *ctx);