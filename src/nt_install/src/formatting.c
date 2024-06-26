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
#include <nt5emul/tui/rectangle.h>
#include <nt5emul/tui/text.h>
#include <nt5emul/tui/input.h>
#include <nt5emul/tui/progress_bar.h>

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <string.h>
#include <stdio.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

void _boot_install_update_step7() {
    float delta = GetFrameTime();

    __state.timer0 += delta;

    if (__state.timer0 >= __state.timer0_max) {
        __state.timer0 = 0.f;
        _boot_install_beginstep8();
    }
}

void _boot_install_draw_step7() {
    Rectangle r;
    r.width = 40;
    r.height = 2;
    r.x = 10;
    r.y = 10;

    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};
    Color blue = (Color){0x00, 0x09, 0xAB, 0xFF};

    renderer_state_t *st = _ntRendererGetState();

    // get render size in characters
    int szX = st->current_window_size.x / __state.base_size.x;
    int szY = st->current_window_size.y / __state.base_size.y;

    // Please wait until Setup formats the partition
    _ntTuiDrawTextCentered(__boot_install_strings[25], 0xFF, 5, gray);
    _ntTuiDrawTextCentered(__state.buffers[4], 0xFF, 7, gray);

    // get percentage of timer
    float p = (__state.timer0 / __state.timer0_max) * 100.f;

    // format string
    snprintf(__state.buffers[3], 64, "%d%c", (int)p, '%');

    int offset = 7;

    // generate frame 1
    r.width = szX - (offset * 2);
    r.height = 6;
    r.x = offset - 1;
    r.y = szY - 11;

    //  Setup is formating...
    _ntTuiDrawFrameDouble(r, gray, __boot_install_strings[44]);

    offset += 5;

    // generate frame 2
    r.width = szX - (offset * 2);
    r.height = 2;
    r.x = offset - 1;
    r.y = szY - 8;

    // draw second frame
    _ntTuiDrawFrame(r, gray, NULL);

    // generate progress bar rectangle

    offset++;

    r.width = szX - (offset * 2);
    r.height = 1;
    r.x = offset - 1;
    r.y = szY - 7;

    _ntTuiDrawProgressBar(p, r, blue, YELLOW);

    _ntTuiDrawTextCentered(__state.buffers[3], 0xFF, r.y - 2, gray);
}