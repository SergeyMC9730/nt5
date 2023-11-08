#include <nt5emul/boot_install.h>

#include <nt5emul/renderer.h>

extern ntinstall_t __state;

// STEP 1

extern void _boot_install_update_step1();
extern void _boot_install_draw_step1();

void _boot_install_begin() {
    _renderer_state.layers[0].draw = _boot_install_draw_step1;
    _renderer_state.layers[0].update = _boot_install_update_step1;
    
    __state.buffers[0] = (char *)MemAlloc(32);
}