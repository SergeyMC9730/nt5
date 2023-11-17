#include <nt5emul/boot_install.h>

#include <string.h>
#include <stdio.h>

#include <nt5emul/bi/text.h>
#include <nt5emul/bi/rectangle.h>

extern char *__boot_install_strings[4];
extern ntinstall_t __state;

void _biDrawBackgroundEx(const char *product_name, const char *help_shortcuts, Color bg_color, Color status_color, Color status_text_color) {
    ClearBackground(bg_color);
    _biTextDraw(product_name, 0, 1, status_color);

    int l = strlen(product_name) + 1;

    for (unsigned int i = 0; i < l; i++) {
        _biTextDraw(__boot_install_strings[2], i, 2, status_color);
    }

    snprintf(__state.buffers[0], 32, __boot_install_strings[3], (1.f / GetFrameTime()));

    _biTextDraw(__state.buffers[0], l + 3, 2, GRAY);

    _biRectangleDraw((Rectangle){0, 29, 85, 1}, status_color);

    _biTextDraw(help_shortcuts, 2, 29, status_text_color);
}

void _biDrawBackground(const char *product_name, const char *help_shortcuts) {
   return _biDrawBackgroundEx(product_name, help_shortcuts, (Color){0x00, 0x09, 0xAB, 0xFF}, (Color){0xA8, 0xA8, 0xA8, 0xFF}, BLACK);
}