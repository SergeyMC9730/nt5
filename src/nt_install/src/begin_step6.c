#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <stdio.h>
#include <string.h>

extern ntinstall_t __state;
extern char *__boot_install_strings[64];

// STEP 6

extern void _boot_install_update_step6();
extern void _boot_install_draw_step6();

void _boot_install_beginstep6(int idx, bi_menu_t *menu) {
    _renderer_state.layers[0].update = _boot_install_update_step6;
    _renderer_state.layers[0].draw = _boot_install_draw_step6;

    // MemFree(__state.buffers[1]); // not an allocated memory pointer actually
    MemFree(__state.buffers[3]);
    __state.buffers[3] = (char *)MemAlloc(32);
}