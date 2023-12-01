#include <nt5emul/boot_install.h>
#include <nt5emul/renderer.h>

#include <stdlib.h>

#include <nt5emul/bi/text.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

void _boot_install_update_step3() {
    // F8=I agree  ESC=I do not agree
    __state.show_input_pointer = __boot_install_strings[18];

    if (IsKeyPressed(KEY_F8) || BOOT_INSTALL_SKIP_TO_COPY) {
        // if F8 key is pressed then go to the next step
        _boot_install_beginstep4();
    }

    else if (IsKeyPressed(KEY_F3)) {
        // exit the program
        exit(0);
    }
}
void _boot_install_draw_step3() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};

    // draw license agreement
    _biTextDraw(__state.buffers[2], 3, 4, gray);

    // F8=I agree  ESC=I do not agree
    __state.show_input_pointer = __boot_install_strings[18];
}