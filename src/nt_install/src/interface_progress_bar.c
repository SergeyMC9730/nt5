#include <nt5emul/bi/progress_bar.h>
#include <nt5emul/bi/rectangle.h>

void _biDrawProgressBar(float percentage, Rectangle position, Color color_bg, Color color_fg) {
    // boundary check
    if (percentage > 100.f) {
        percentage = 100.f; 
    } else if (percentage < 0.f) {
        percentage = 0.f;
    }

    // draw background rectangle
    _biRectangleDraw(position, color_bg);

    // calculate size for a foreground rectangle
    position.width *= (percentage / 100.f);

    // draw rectangle
    _biRectangleDraw(position, color_fg);
}