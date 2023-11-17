#include <nt5emul/bi/frame.h>
#include <nt5emul/bi/text.h>

void _biDrawFrameEx(Rectangle r, Color col, const char **mapping) {
    // draw up side

    for (int i = 0; i < r.width; i++) {
        char *to_draw = mapping[0]; // ─

        if (i == 0) to_draw = mapping[1]; // ┌
        if (i == r.width) to_draw = mapping[2]; // ┐

        _biTextDraw(to_draw, r.x + i, r.y, col);
    }

    // draw left side

    for (int i = 0; i < r.height; i++) {
        char *to_draw = mapping[3]; // │

        if (i == 0) to_draw = mapping[1]; // ┌
        if (i == r.height) to_draw = mapping[4]; // └

        _biTextDraw(to_draw, r.x, r.y + i, col);
    }

    // draw right side

    for (int i = 0; i < r.height; i++) {
        char *to_draw = mapping[3]; // │

        if (i == 0) to_draw = mapping[2]; // ┐
        if (i == r.height) to_draw = mapping[5]; // ┘

        _biTextDraw(to_draw, r.x + r.width, r.y + i, col);
    }

    // draw down side

    for (int i = 0; i < (r.width + 1); i++) {
        char *to_draw = mapping[6]; // ─

        if (i == 0) to_draw = mapping[4]; // └
        if (i == r.width) to_draw = mapping[5]; // ┘

        _biTextDraw(to_draw, r.x + i, r.y + r.height, col);
    }

    return;
}

void _biDrawFrame(Rectangle r, Color col) {
    const char *mapping[] = {
        "─", "┌", "┐", "│", "└", "┘", "─"
    };

    return _biDrawFrameEx(r, col, mapping);
}
