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

#include <nt5emul/boot_install.h>
#include <nt5emul/renderer.h>

#include <stdlib.h>

#include <nt5emul/tui/text.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

void _boot_install_update_step3() {
    // F8=I agree  ESC=I do not agree
    __state.show_input_pointer = __boot_install_strings[18];

    if (IsKeyPressed(KEY_F8) || BOOT_INSTALL_SKIP_TO_COPY) {
        // if F8 key is pressed then go to the next step
        _boot_install_beginstep4();
    }

    else if (IsKeyPressed(KEY_F3)) {
        // exit the program
        exit(0);
    }
}
void _boot_install_draw_step3() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};

    // draw license agreement
    _ntTuiDrawText(__state.buffers[2], 3, 4, gray);

    // F8=I agree  ESC=I do not agree
    __state.show_input_pointer = __boot_install_strings[18];
}