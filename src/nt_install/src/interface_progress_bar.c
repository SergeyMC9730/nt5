#include <nt5emul/bi/progress_bar.h>
#include <nt5emul/bi/rectangle.h>

void _biDrawProgressBar(float percentage, Rectangle position, Color color_bg, Color color_fg) {
    if (percentage > 100.f) {
        percentage = 100.f; 
    }

    _biRectangleDraw(position, color_bg);

    position.width *= percentage;

    _biRectangleDraw(position, color_fg);
}