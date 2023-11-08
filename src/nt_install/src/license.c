#include <nt5emul/boot_install.h>
#include <nt5emul/renderer.h>

#include <stdlib.h>

extern char *__boot_install_strings[64];
extern ntinstall_t __state;

void _boot_install_update_step3() {
    if (IsKeyPressed(KEY_F8)) {
        
    }
}
void _boot_install_draw_step3() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};

    _biDrawBackground(__boot_install_strings[16], __boot_install_strings[18]);

    _biTextDraw(__state.buffers[2], 3, 4, gray);
}