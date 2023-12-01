#include <raylib.h>

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

// expose internal values

extern ntinstall_t __state; // installation state

// expose NT renderer
extern renderer_state_t _renderer_state;

#ifndef NULL
#define NULL ((void *)0)
#endif

void _boot_install_backgroundInit() {
    _renderer_state.layers[0].draw = _boot_install_drawBackground;
    _renderer_state.layers[0].update = NULL;
}

void _boot_install_drawBackground() {
    if (__state.halt) return;

    Color blue = (Color){0x00, 0x09, 0xAB, 0xFF};

    const char *status = (__state.status_bar_is_error) ? __state.status_bar_error :  __state.status_bar_label;

    if (!__state.status_bar_is_error) {
        _biDrawBackground(__state.product_name_label, status);
    } else {
        _biDrawBackgroundEx(__state.product_name_label, status, blue, RED, WHITE);
    }
}