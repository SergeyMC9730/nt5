#include <nt5emul/boot_install.h>
#include <nt5emul/renderer.h>

// STEP 2

// expose renderer for this step
extern void _boot_install_update_step2();
extern void _boot_install_draw_step2();

// expose NT renderer
extern renderer_state_t _renderer_state;

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state;

void _boot_install_beginstep2() {
    _renderer_state.layers[1].draw = _boot_install_draw_step2;
    _renderer_state.layers[1].update = _boot_install_update_step2;

    //  NT Professional Setup
    __state.product_name_label = __boot_install_strings[7];

    // ENTER=Continue  R=Repair  F3=Quit
    __state.status_bar_label = __boot_install_strings[15];
}