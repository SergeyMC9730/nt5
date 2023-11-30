#include <nt5emul/boot_install.h>
#include <nt5emul/renderer.h>

#include <stdlib.h>

#include <string.h>

#include <stdio.h>

#include <signal.h>
#include <unistd.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// expose timer
extern void _boot_install_timer(void(*callback)(), float seconds);

bool _bi1stop = false;

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_update_step1_text() {
    if (_bi1stop) return;

    int lines = 3;

    __state.buffers[1] = __boot_install_strings[4 + (__state.idx0 % lines)];

    __state.status_bar_label = __state.buffers[1];

    __state.idx0++;

    if (__state.idx0 >= (lines + 1)) {
        _boot_install_beginstep2();
    } else {
        _boot_install_timer(_boot_install_update_step1_text, 5.f);
    }
}

void _boot_install_update1_step1() {
    if (IsKeyPressed(KEY_F6)) {
        // Cannot load driver: Not Implemented
        _boot_install_throw_error(__boot_install_strings[41]);
    }
    else if (IsKeyPressed(KEY_F2)) {
        // Cannot load ASR: Not Implemented
        _boot_install_throw_error(__boot_install_strings[42]);
    }
}

void _boot_install_update_step1() {
    // load codepoints
    int codepointCount = 0;
    int *codepoints = LoadCodepoints(__boot_install_strings[0], &codepointCount);

    // load font with them
    __state.font = LoadFontEx("ntresources/Px437_IBM_VGA_8x16.ttf", 16, codepoints, codepointCount);
    // set base font size
    __state.base_size = (Vector2){8, 16};
    // free allocation done by LoadCodepoints
    free(codepoints);
    // scroll help shortcuts
    _boot_install_update_step1_text();

    __state.product_name_label = __boot_install_strings[1];
    __state.status_bar_label = __state.buffers[1];
    
    _renderer_state.layers[1].update = _boot_install_update1_step1;

    #if BOOT_INSTALL_SKIP_STEP1 == 1
    _boot_install_beginstep2();
    _bi1stop = true;
    #endif
}

void _boot_install_draw_step1() {  

}
