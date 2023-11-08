#include <nt5emul/boot_install.h>
#include <nt5emul/renderer.h>

extern ntinstall_t __state;
extern char *__boot_install_strings[64];

// STEP 3

extern void _boot_install_update_step3();
extern void _boot_install_draw_step3();

void _boot_install_beginstep3() {
    _renderer_state.layers[0].draw = _boot_install_draw_step3;
    _renderer_state.layers[0].update = _boot_install_update_step3;

    __state.buffers[2] = LoadFileText(__boot_install_strings[17]);

    for (int i = 0; i < 20; i++) {
        printf("%d - %s\n", i, __boot_install_strings[i]);
    }
}