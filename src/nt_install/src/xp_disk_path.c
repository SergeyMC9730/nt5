#include <nt5emul/bi/frame.h>
#include <nt5emul/bi/rectangle.h>
#include <nt5emul/bi/text.h>
#include <nt5emul/bi/input.h>

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

#define FIELD_SIZE 64

void _boot_install_update_step6() {
    _biUpdateInput(__state.buffers[3], FIELD_SIZE);

    if (IsKeyPressed(KEY_ENTER)) {
        if (DirectoryExists(__state.buffers[3])) {
            _boot_install_beginstep7();
        } else {
            // Entered path does not exist!
            _boot_install_throw_error(__boot_install_strings[36]);
        }
    }
}

void _boot_install_draw_step6() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};

    _biTextDraw(__boot_install_strings[35], 3, 4, gray);

    size_t l = FIELD_SIZE;

    int centerX = (80 - l) / 2;

    _biDrawInput(__state.buffers[3], l, (Vector2){centerX, 15}, BLACK, WHITE);
}