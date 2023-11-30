#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <unistd.h>

#include <sys/time.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// STEP 6

extern void _boot_install_update_step6();
extern void _boot_install_draw_step6();

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_beginstep6(int idx, bi_menu_t *menu) {
    _renderer_state.layers[1].update = _boot_install_update_step6;
    _renderer_state.layers[1].draw = _boot_install_draw_step6;

    // reallocate and fill buffer 3 with zeros
    __state.buffers[3] = MemRealloc(__state.buffers[3], 64);
    memset(__state.buffers[3], 0, 64);
}