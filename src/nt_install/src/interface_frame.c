#include <nt5emul/bi/frame.h>
#include <nt5emul/bi/text.h>

// null check
#ifndef NULL
#define NULL (void *)0
#endif

void _biDrawFrameEx(Rectangle r, Color col, const char **mapping) {
    if (mapping == NULL) return;
    
    unsigned char index = 0;

    // draw up side

    for (int i = 0; i < r.width; i++) {
        index = 0; // ─

        if (i == 0) index = 1; // ┌
        else if (i == r.width) index = 2; // ┐

        _biTextDraw(mapping[index], r.x + i, r.y, col);
    }

    // draw left side

    for (int i = 0; i < r.height; i++) {
        index = 3; // │

        if (i == 0) index = 1; // ┌
        else if (i == r.height) index = 4; // └

        _biTextDraw(mapping[index], r.x, r.y + i, col);
    }

    // draw right side

    for (int i = 0; i < r.height; i++) {
        index = 3; // │

        if (i == 0) index = 2; // ┐
        else if (i == r.height) index = 3; // ┘

        _biTextDraw(mapping[index], r.x + r.width, r.y + i, col);
    }

    // draw down side

    for (int i = 0; i < (r.width + 1); i++) {
       index = 6; // ─

        if (i == 0) index = 4; // └
        else if (i == r.width) index = 5; // ┘

        _biTextDraw(mapping[index], r.x + i, r.y + r.height, col);
    }

    return;
}

void _biDrawFrame(Rectangle r, Color col) {
    const char *mapping[] = {
        "─", "┌", "┐", "│", "└", "┘", "─"
    };

    return _biDrawFrameEx(r, col, mapping);
}
