#include <nt5emul/boot_install.h>
#include <nt5emul/renderer.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// STEP 3

// expose renderer for this step
extern void _boot_install_update_step3();
extern void _boot_install_draw_step3();

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_beginstep3() {
    _renderer_state.layers[0].draw = _boot_install_draw_step3;
    _renderer_state.layers[0].update = _boot_install_update_step3;

    // check if license exist
    if (FileExists(__boot_install_strings[17])) {
        __state.buffers[2] = LoadFileText(__boot_install_strings[17]);

        return;
    }

    // if not, allocate empty string
    __state.buffers[2] = (char *)MemAlloc(64);
}