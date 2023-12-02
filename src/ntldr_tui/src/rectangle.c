#include <nt5emul/tui/environment.h>

extern struct nt_tui_environment _ntTuiEnvironment;

void _ntTuiDrawRectangle(Rectangle r, Color col) {
    DrawRectangle(
                r.x * _ntTuiEnvironment.base_font_size.x, 
                r.y * _ntTuiEnvironment.base_font_size.y, 
                r.width * _ntTuiEnvironment.base_font_size.x, 
                r.height * _ntTuiEnvironment.base_font_size.y, 
                
                col
    );
}