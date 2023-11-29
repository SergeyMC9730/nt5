#include <nt5emul/boot_install.h>
#include <nt5emul/renderer.h>

#include <nt5emul/bi/text.h>
#include <nt5emul/bi/frame.h>

#include <stdio.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// STEP 4

void _boot_install_update_step4() {
    _biUpdateMenu(&__state.menu0);
}
void _boot_install_draw_step4() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};
    Color bg = (Color){0x00, 0x09, 0xAB, 0xFF};
    
    _biDrawBackground(__boot_install_strings[7], __boot_install_strings[23]);

    _biTextDraw(__boot_install_strings[19], 3, 4, gray);

    _biDrawMenu(__state.menu0);

    _biDrawFrame((Rectangle){2, 14, 75, 13}, gray);

    snprintf(__state.buffers[4], 256, __boot_install_strings[20], 16 * 1024, __state.menu0.selected_item, 0, 0);

    _biTextDraw(__state.buffers[4], 3, 15, gray);
}
