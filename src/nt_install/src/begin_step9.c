#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// expose NT renderer
extern renderer_state_t _renderer_state;

// STEP 9

extern void _boot_install_update_step9();
extern void _boot_install_draw_step9();

void _boot_install_beginstep9() {
    // free buffers
    MemFree( __state.buffers[3]);
    MemFree( __state.buffers[4]);
    MemFree( __state.buffers[5]);
    MemFree( __state.buffers[6]);
    MemFree( __state.buffers[7]);
    
    // Creating information file config.json...
    __state.status_bar_label = __boot_install_strings[56];

    _renderer_state.layers[1].update = _boot_install_update_step9;
    _renderer_state.layers[1].draw = _boot_install_draw_step9;
}