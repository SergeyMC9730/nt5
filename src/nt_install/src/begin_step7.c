#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <string.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// STEP 7

extern void _boot_install_update_step7();
extern void _boot_install_draw_step7();

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_beginstep7() {
    _renderer_state.layers[1].update = _boot_install_update_step7;
    _renderer_state.layers[1].draw = _boot_install_draw_step7;

    // reset buffer 3
    memset(__state.buffers[3], 0, 64);

    __state.status_bar_label = "";
}