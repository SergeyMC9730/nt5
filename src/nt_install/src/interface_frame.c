#include <nt5emul/bi/frame.h>
#include <nt5emul/bi/text.h>

void _biDrawFrame(Rectangle r, Color col) {
    // draw up side

    for (int i = 0; i < r.width; i++) {
        char *to_draw = "─";

        if (i == 0) to_draw = "┌";
        if (i == r.width) to_draw = "┐";

        _biTextDraw(to_draw, r.x + i, r.y, col);
    }

    // draw left side

    for (int i = 0; i < r.height; i++) {
        char *to_draw = "│";

        if (i == 0) to_draw = "┌";
        if (i == r.height) to_draw = "└";

        _biTextDraw(to_draw, r.x, r.y + i, col);
    }

    // draw right side

    for (int i = 0; i < r.height; i++) {
        char *to_draw = "│";

        if (i == 0) to_draw = "┐";
        if (i == r.height) to_draw = "┘";

        _biTextDraw(to_draw, r.x + r.width, r.y + i, col);
    }

    // draw down side

    for (int i = 0; i < (r.width + 1); i++) {
        char *to_draw = "─";

        if (i == 0) to_draw = "└";
        if (i == r.width) to_draw = "┘";

        _biTextDraw(to_draw, r.x + i, r.y + r.height, col);
    }

    return;
}
