#include <nt5emul/bi/frame.h>
#include <nt5emul/bi/rectangle.h>
#include <nt5emul/bi/text.h>
#include <nt5emul/bi/input.h>

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

extern ntinstall_t __state;
extern char *__boot_install_strings[64];

#define FIELD_SIZE 64

void _boot_install_update_step6() {
    static char *files[] = {
        "123", "456", "789"
    };

    _biUpdateInput(__state.buffers[3], FIELD_SIZE);
}

void _boot_install_draw_step6() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};

    _biDrawBackground(__boot_install_strings[7], __boot_install_strings[34]);

    _biTextDraw(__boot_install_strings[35], 3, 4, gray);

    size_t l = FIELD_SIZE;

    _biDrawInput(__state.buffers[3], l, (Vector2){(80 - l) / 2, 15}, BLACK, WHITE);
}