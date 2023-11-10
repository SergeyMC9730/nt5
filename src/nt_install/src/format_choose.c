#include <nt5emul/bi/text.h>
#include <nt5emul/bi/menu.h>

#include <nt5emul/boot_install.h>

// STEP 5

extern ntinstall_t __state;
extern char *__boot_install_strings[64];

void _boot_install_update_step5() {
    _biUpdateMenu(&__state.menu0);
}
void _boot_install_draw_step5() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};
    Color bg = (Color){0x00, 0x09, 0xAB, 0xFF};
    
    _biDrawBackground(__boot_install_strings[7], __boot_install_strings[34]);

    _biTextDraw(__state.buffers[3], 3, 4, gray);

    _biDrawMenu(__state.menu0);
}