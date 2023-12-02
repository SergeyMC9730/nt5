#include <nt5emul/tui/text.h>
#include <nt5emul/tui/menu.h>

#include <nt5emul/boot_install.h>

// STEP 5

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

void _boot_install_update_step5() {
    _ntUpdateMenu(&__state.menu0);

    #if BOOT_INSTALL_SKIP_TO_COPY == 1
    __state.menu0.click_handler(0, &__state.menu0);
    #endif
}
void _boot_install_draw_step5() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF}; // gray
    Color bg = (Color){0x00, 0x09, 0xAB, 0xFF}; // blue

    // draw string from third buffer
    _ntTuiDrawText(__state.buffers[3], 3, 4, gray);

    // draw menu
    _ntTuiDrawMenu(__state.menu0);
}