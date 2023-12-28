#pragma once

#include <cterm/applications/api.h>
#include <raylib.h>

struct module_state {
    cterm_t *runtime;

    Texture2D logo_texture;
    Color transition_color;

    int frames;

    bool init_complete;

    void (*old_draw)(void *user);
    void (*old_update)(void *user);
    void *old_ctx;
};

extern struct module_state _state;