#include <nt5emul/boot_install.h>

#include <nt5emul/renderer.h>

// expose internal values

extern ntinstall_t __state; // installation state

// STEP 1

extern void _boot_install_update_step1();
extern void _boot_install_draw_step1();

extern void _biUpdatePointer();

extern void _boot_install_timer(void(*callback)(), float seconds);

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_begin() {
    SetTargetFPS(30);

    _renderer_state.layers[0].draw = _boot_install_draw_step1;
    _renderer_state.layers[0].update = _boot_install_update_step1;

    _renderer_state.layers[1].update = _boot_install_shortcuts_update;
    
    __state.buffers[0] = (char *)MemAlloc(32);

    __state.show_input_pointer = true;

    _boot_install_timer(_biUpdatePointer, 0.5f);
}