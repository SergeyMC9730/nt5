#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <stdio.h>
#include <string.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

char *__boot_install_objects01[4] = {0};

// STEP 5

extern void _boot_install_update_step5();
extern void _boot_install_draw_step5();

// STEP 6

extern void _boot_install_beginstep6(int idx, struct nt_tui_menu *menu);

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_beginstep5(int idx, struct nt_tui_menu *menu) {
    for (int i = 0; i < 4; i++) {
        /*
            push items:
             * ntfs format (quick)
             * fat format (quick)
             * ntfs format
             * fat format
        */
        __boot_install_objects01[i] = __boot_install_strings[30 + i];
    }

    // update menu with new items
    __state.menu0.items_total = 4;
    __state.menu0.objects = (const char **)__boot_install_objects01;
    __state.menu0.selected_item = 0;
    __state.menu0.y--;
    __state.menu0.click_handler = _boot_install_beginstep6;

    // free buffers
    MemFree(__state.buffers[3]);
    MemFree(__state.buffers[4]);

    // allocate a new one for string formatting purposes
    __state.buffers[4] = (char *)MemAlloc(256);
    // format string %d MB Disk %d at Id %d on bus %d on atapi [MBR]
    snprintf(__state.buffers[4], 256, __boot_install_strings[20], 16 * 1024, idx, 0, 0);

    // calculate allocation size
    size_t sz = 512 + strlen(__state.buffers[4]);

    // allocate a new buffer
    __state.buffers[3] = (char *)MemAlloc(sz);

    // format stirng
    snprintf(__state.buffers[3], sz, __boot_install_strings[29], __state.buffers[4]);

    // unload license agreement
    UnloadFileText(__state.buffers[2]);

    // format string on %d MB Disk %d at Id %d on bus %d on atapi [MBR].
    snprintf(__state.buffers[4], 256, __boot_install_strings[28], 16 * 1024, idx, 0, 0);

    _renderer_state.layers[1].update = _boot_install_update_step5;
    _renderer_state.layers[1].draw = _boot_install_draw_step5;

    // ENTER=Continue  ESC=Cancel
    __state.status_bar_label = __boot_install_strings[34];
}