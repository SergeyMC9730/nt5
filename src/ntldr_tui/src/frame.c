/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  SergeyMC9730

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact SergeyMC9730 -- @dogotrigger in Discord
*/

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