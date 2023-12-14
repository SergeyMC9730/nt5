#pragma once

#include <nt5emul/dwm/context.h>

struct dwm_button {
    Rectangle button;

    const char *text;

    struct dwm_bool activated;
    struct dwm_bool howered;
};

// if user clicks to button function returns true
bool _ntDrawDWMButton(struct dwm_context *ctx, struct dwm_button *btn);