#include <nt5emul/tui/frame.h>
#include <nt5emul/tui/text.h>

// null check
#ifndef NULL
#define NULL (void *)0
#endif

void _ntTuiDrawFrameEx(Rectangle r, Color col, const char **mapping, const char *description) {
    if (mapping == NULL) return;
    
    unsigned char index = 0;

    // draw up side

    for (int i = 0; i < r.width; i++) {
        index = 0; // ─

        if (i == 0) index = 1; // ┌
        else if (i == r.width) index = 2; // ┐

        _ntTuiDrawText(mapping[index], r.x + i, r.y, col);
    }

    // draw left side

    for (int i = 0; i < r.height; i++) {
        index = 3; // │

        if (i == 0) index = 1; // ┌
        else if (i == r.height) index = 4; // └

        _ntTuiDrawText(mapping[index], r.x, r.y + i, col);
    }

    // draw right side

    for (int i = 0; i < r.height; i++) {
        index = 3; // │

        if (i == 0) index = 2; // ┐
        else if (i == r.height) index = 3; // ┘

        _ntTuiDrawText(mapping[index], r.x + r.width, r.y + i, col);
    }

    // draw down side

    for (int i = 0; i < (r.width + 1); i++) {
       index = 6; // ─

        if (i == 0) index = 4; // └
        else if (i == r.width) index = 5; // ┘

        _ntTuiDrawText(mapping[index], r.x + i, r.y + r.height, col);
    }

    // draw text

    if (description == NULL) return;

    Vector2 tPos = {
        r.x + 1,
        r.y + 1
    };

    _ntTuiDrawText(description, tPos.x, tPos.y, col);

    return;
}

void _ntTuiDrawFrame(Rectangle r, Color col, const char *description) {
    const char *mapping[] = {
        "─", "┌", "┐", "│", "└", "┘", "─"
    };

    return _ntTuiDrawFrameEx(r, col, mapping, description);
}

void _ntTuiDrawFrameDouble(Rectangle r, Color col, const char *description) {
    const char *mapping[] = {
        "═", "╔", "╗", "║", "╚", "╝", "═"
    };

    return _ntTuiDrawFrameEx(r, col, mapping, description);
}