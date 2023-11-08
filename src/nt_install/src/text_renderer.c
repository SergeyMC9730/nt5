#include <nt5emul/boot_install.h>

extern ntinstall_t __state;

void _biTextDraw(const char *str, unsigned char x, unsigned char y, Color col) {
    DrawTextEx(__state.font, str, (Vector2){x * __state.base_size.x, y * __state.base_size.y}, 16, 0.f, col);
}
void _biRectangleDraw(Rectangle r, Color col) {
    DrawRectangle(r.x * __state.base_size.x, r.y * __state.base_size.y, r.width * __state.base_size.x, r.height * __state.base_size.y, col);
}