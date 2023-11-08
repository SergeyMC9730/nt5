#include <nt5emul/boot_install.h>
#include <nt5emul/renderer.h>

#include <stdlib.h>

#include <nt5emul/bi/text.h>

extern char *__boot_install_strings[64];

void _boot_install_update_step2() {
    if (IsKeyPressed(KEY_F3)) {
        exit(0);
    }

    if (IsKeyPressed(KEY_R)) {}

    if (IsKeyPressed(KEY_ENTER)) {
        _boot_install_beginstep3();
    }
}
void _boot_install_draw_step2() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};

    _biDrawBackground(__boot_install_strings[7], __boot_install_strings[15]);

    _biTextDraw(__boot_install_strings[8], 3, 4, WHITE);

    _biTextDraw(__boot_install_strings[9], 3, 6, gray);
    _biTextDraw(__boot_install_strings[10], 3, 7, gray);


    _biTextDraw(__boot_install_strings[11], 4, 9, gray);

    _biTextDraw(__boot_install_strings[12], 4, 11, gray);
    _biTextDraw(__boot_install_strings[13], 4, 12, gray);

    _biTextDraw(__boot_install_strings[14], 4, 14, gray);
}