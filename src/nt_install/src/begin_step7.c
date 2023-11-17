#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

extern ntinstall_t __state;
extern char *__boot_install_strings[64];

// STEP 7

extern void _boot_install_update_step7();
extern void _boot_install_draw_step7();

void _boot_install_beginstep7() {
    _renderer_state.layers[0].update = _boot_install_update_step7;
    _renderer_state.layers[0].draw = _boot_install_draw_step7;

    MemFree(__state.buffers[3]);
}