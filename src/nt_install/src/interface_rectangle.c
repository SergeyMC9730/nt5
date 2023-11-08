#include <nt5emul/boot_install.h>

extern ntinstall_t __state;

void _biRectangleDraw(Rectangle r, Color col) {
    DrawRectangle(r.x * __state.base_size.x, r.y * __state.base_size.y, r.width * __state.base_size.x, r.height * __state.base_size.y, col);
}