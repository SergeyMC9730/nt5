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

#include <nt5emul/tui/text.h>
#include <nt5emul/tui/input.h>

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

#define FIELD_SIZE 64

void _boot_install_update_step6() {
    _ntUpdateInput(__state.buffers[3], FIELD_SIZE);

    if (IsKeyPressed(KEY_ENTER)) {
        if (DirectoryExists(__state.buffers[3])) {
            _boot_install_beginstep7();
        } else {
            // Entered path does not exist!
            _boot_install_throw_error(__boot_install_strings[36]);
        }
    }
}

void _boot_install_draw_step6() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};

    _ntTuiDrawText(__boot_install_strings[35], 3, 4, gray);

    size_t l = FIELD_SIZE;

    int centerX = (80 - l) / 2;

    _ntTuiDrawInput(__state.buffers[3], l, (Vector2){centerX, 15}, BLACK, WHITE);
}