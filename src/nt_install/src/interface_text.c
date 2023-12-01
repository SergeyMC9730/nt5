#include <nt5emul/boot_install.h>

// expose internal values

extern ntinstall_t __state; // installation state

// null check
#ifndef NULL
#define NULL (void *)0
#endif

#include <string.h>

void _biTextDraw(const char *str, unsigned char x, unsigned char y, Color col) {
    if (str == NULL) return;
    
    DrawTextEx(__state.font, str, (Vector2){x * __state.base_size.x, y * __state.base_size.y}, 16, 0.f, col);
}

void _biTextDrawCentered(const char *str, signed char x, signed char y, Color col) {
    if (str == NULL) return;
    
    size_t len = strlen(str);

    Vector2 pos = {x, y};

    if ((unsigned char)x == 0xFF) {
        // get render width in characters
        int szX = GetRenderWidth() / __state.base_size.x;

        // get centered X position
        pos.x = (int)(((szX - len) / 2) + x);
    }
    if ((unsigned char)y == 0xFF) {
        // TEMP

        // get render heigth in characters
        int szY = GetRenderHeight() / __state.base_size.y;

        // get centered Y position
        pos.y = (int)(((szY - 1) / 2) + y);
    }

    return _biTextDraw(str, (unsigned char)pos.x, (unsigned char)pos.y, col);
}