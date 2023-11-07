#include <nt5emul/boot_install.h>
#include <nt5emul/renderer.h>

#include <raylib.h>

#include <stdlib.h>

#include <string.h>

typedef struct ntinstall_t {
    Font font;
    Vector2 base_size;

    char *buffers[16];
} ntinstall_t;

ntinstall_t __state = {};

extern char *__boot_install_strings[4];

void _boot_install_update1() {
    SetWindowSize(640, 400);

    int codepointCount = 0;
    int *codepoints = LoadCodepoints(__boot_install_strings[0], &codepointCount);

    __state.font = LoadFontEx("ntresources/Px437_IBM_VGA_8x16.ttf", 16, codepoints, codepointCount);

    __state.base_size = (Vector2){8, 16};

    free(codepoints);

    _renderer_state.layers[0].update = NULL;
}

void _biTextDraw(const char *str, unsigned char x, unsigned char y, Color col) {
    DrawTextEx(__state.font, str, (Vector2){x * __state.base_size.x, y * __state.base_size.y}, 16, 1.f, col);
}

void _boot_install_draw() {
    Color bg = (Color){0x00, 0x09, 0xAB, 0xFF};

    ClearBackground(bg);
    _biTextDraw(__boot_install_strings[1], 0, 1, WHITE);

    for (unsigned int i = 0; i < strlen(__boot_install_strings[1]) + 3; i++) {
        _biTextDraw(__boot_install_strings[2], i, 2, WHITE);
    }
}

void _boot_install_begin() {
    _renderer_state.layers[0].draw = _boot_install_draw;
    _renderer_state.layers[0].update = _boot_install_update1;
}