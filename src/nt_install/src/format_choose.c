#include <nt5emul/bi/text.h>
#include <nt5emul/bi/menu.h>

#include <nt5emul/boot_install.h>

// STEP 5

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

void _boot_install_update_step5() {
    _biUpdateMenu(&__state.menu0);
}
void _boot_install_draw_step5() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF}; // gray
    Color bg = (Color){0x00, 0x09, 0xAB, 0xFF}; // blue

    // draw string from third buffer
    _biTextDraw(__state.buffers[3], 3, 4, gray);

    // draw menu
    _biDrawMenu(__state.menu0);
}