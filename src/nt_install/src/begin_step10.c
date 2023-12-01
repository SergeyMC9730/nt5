#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>
#include <nt5emul/timer.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// expose NT renderer
extern renderer_state_t _renderer_state;

// STEP 10

extern void _boot_install_update_step10();
extern void _boot_install_draw_step10();
extern void _ntInstallTimer10();

void _boot_install_beginstep10() {
    __state.buffers[3] = (char *)MemAlloc(128);

    // ENTER=Restart Computer
    __state.status_bar_label = __boot_install_strings[54];

    _renderer_state.layers[1].update = _boot_install_update_step10;
    _renderer_state.layers[1].draw = _boot_install_draw_step10;

    _ntInstallTimer(_ntInstallTimer10, 1.f);
}