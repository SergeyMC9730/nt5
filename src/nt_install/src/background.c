#include <nt5emul/boot_install.h>

#include <string.h>
#include <stdio.h>

#include <nt5emul/bi/text.h>
#include <nt5emul/bi/rectangle.h>

extern char *__boot_install_strings[4];
extern ntinstall_t __state;

void _biDrawBackground(const char *product_name, const char *help_shortcuts) {
    Color bg = (Color){0x00, 0x09, 0xAB, 0xFF};
    Color help_gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};

    ClearBackground(bg);
    _biTextDraw(product_name, 0, 1, help_gray);

    int l = strlen(product_name) + 1;

    for (unsigned int i = 0; i < l; i++) {
        _biTextDraw(__boot_install_strings[2], i, 2, help_gray);
    }

    snprintf(__state.buffers[0], 32, __boot_install_strings[3], GetFPS());

    _biTextDraw(__state.buffers[0], l + 3, 2, GRAY);

    _biRectangleDraw((Rectangle){0, 29, 85, 1}, help_gray);

    _biTextDraw(help_shortcuts, 2, 29, BLACK);
}