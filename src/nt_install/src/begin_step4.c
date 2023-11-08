#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <stdio.h>
#include <string.h>

extern ntinstall_t __state;
extern char *__boot_install_strings[64];

char *__boot_install_objects00[1] = {
    "QWE"
};

// STEP 4

extern void _boot_install_update_step4();
extern void _boot_install_draw_step4();

// STEP 5

void _boot_install_beginstep4() {
    __state.buffers[3] = MemAlloc(256);
    __state.buffers[4] = MemAlloc(256);

    const char *s1 = __boot_install_strings[21];

    snprintf(__state.buffers[3], 256, "     %s               %d MB", s1, 16 * 1024);

    size_t occupied_space = strlen(__state.buffers[3]);
    int spaces = 80 - occupied_space - 14 + 2;
    int i = 0;

    while (i < spaces) {
        strcat(__state.buffers[4], " ");
        i++;
    }

    strcat(__state.buffers[3], __state.buffers[4]);

    // MemFree(__state.buffers[4]);

    __boot_install_objects00[0] = __state.buffers[3];

    __state.menu0.items_total = 1;
    __state.menu0.objects = __boot_install_objects00;
    __state.menu0.click_handler = _boot_install_beginstep5;
    __state.menu0.y = 17;
    __state.menu0.x = 5;

    _renderer_state.layers[0].draw = _boot_install_draw_step4;
    _renderer_state.layers[0].update = _boot_install_update_step4;
}