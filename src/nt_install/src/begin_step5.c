#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <stdio.h>
#include <string.h>

extern ntinstall_t __state;
extern char *__boot_install_strings[64];

char *__boot_install_objects01[4] = {
    
};

// STEP 5

extern void _boot_install_update_step5();
extern void _boot_install_draw_step5();

// STEP 6

extern void _boot_install_beginstep6(int idx, bi_menu_t *menu);

void _boot_install_beginstep5(int idx, bi_menu_t *menu) {
    for (int i = 0; i < 4; i++) {
        __boot_install_objects01[i] = __boot_install_strings[30 + i];
    }

    __state.menu0.items_total = 4;
    __state.menu0.objects = (const char **)__boot_install_objects01;
    __state.menu0.selected_item = 0;
    __state.menu0.y--;
    __state.menu0.click_handler = _boot_install_beginstep6;

    MemFree(__state.buffers[3]);
    MemFree(__state.buffers[4]);

    __state.buffers[4] = (char *)MemAlloc(256);

    snprintf(__state.buffers[4], 256, __boot_install_strings[20], 16 * 1024, idx, 0, 0);

    size_t sz = 512 + strlen(__state.buffers[4]);

    __state.buffers[3] = (char *)MemAlloc(sz);

    snprintf(__state.buffers[3], sz, __boot_install_strings[29], __state.buffers[4]);

    UnloadFileText(__state.buffers[2]);

    snprintf(__state.buffers[4], 256, __boot_install_strings[28], 16 * 1024, idx, 0, 0);

    _renderer_state.layers[0].update = _boot_install_update_step5;
    _renderer_state.layers[0].draw = _boot_install_draw_step5;
}