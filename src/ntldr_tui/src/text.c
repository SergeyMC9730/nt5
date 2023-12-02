#include <nt5emul/tui/environment.h>

extern struct nt_tui_environment _ntTuiEnvironment;

// null check
#ifndef NULL
#define NULL (void *)0
#endif

#include <string.h>

void _ntTuiDrawText(const char *str, unsigned char x, unsigned char y, Color col) {
    if (str == NULL) return;
    
    DrawTextEx(_ntTuiEnvironment.font, str, (Vector2){x * _ntTuiEnvironment.base_font_size.x, y * _ntTuiEnvironment.base_font_size.y}, 16, 0.f, col);
}

void _ntTuiDrawTextCentered(const char *str, signed char x, signed char y, Color col) {
    if (str == NULL) return;
    
    size_t len = strlen(str);

    Vector2 pos = {x, y};

    if ((unsigned char)x == 0xFF) {
        // get render width in characters
        int szX = GetRenderWidth() / _ntTuiEnvironment.base_font_size.x;

        // get centered X position
        pos.x = (int)(((szX - len) / 2) + x);
    }
    if ((unsigned char)y == 0xFF) {
        // TEMP

        // get render heigth in characters
        int szY = GetRenderHeight() / _ntTuiEnvironment.base_font_size.y;

        // get centered Y position
        pos.y = (int)(((szY - 1) / 2) + y);
    }

    return _ntTuiDrawText(str, (unsigned char)pos.x, (unsigned char)pos.y, col);
}