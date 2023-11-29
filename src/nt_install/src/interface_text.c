#include <nt5emul/boot_install.h>

// expose internal values

extern ntinstall_t __state; // installation state

// null check
#ifndef NULL
#define NULL (void *)0
#endif

void _biTextDraw(const char *str, unsigned char x, unsigned char y, Color col) {
    if (str == NULL) return;
    
    DrawTextEx(__state.font, str, (Vector2){x * __state.base_size.x, y * __state.base_size.y}, 16, 0.f, col);
}