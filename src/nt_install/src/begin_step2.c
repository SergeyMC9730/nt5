#include <nt5emul/boot_install.h>
#include <nt5emul/renderer.h>

// STEP 2

// expose renderer for this step
extern void _boot_install_update_step2();
extern void _boot_install_draw_step2();

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_beginstep2() {
    _renderer_state.layers[0].draw = _boot_install_draw_step2;
    _renderer_state.layers[0].update = _boot_install_update_step2;
}