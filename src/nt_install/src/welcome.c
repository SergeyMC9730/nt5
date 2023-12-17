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

void _boot_install_update_step2() {
    if (IsKeyPressed(KEY_F3)) {
        exit(0);
    }

    // recovery option
    if (IsKeyPressed(KEY_R)) {
        // Cannot load Recovery Console: Not Implemented
        _boot_install_throw_error(__boot_install_strings[43]);
    }

    if (IsKeyPressed(KEY_ENTER) || BOOT_INSTALL_SKIP_TO_COPY) {
        _boot_install_beginstep3();
    }
}
void _boot_install_draw_step2() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};

    // print welcome text

    _ntTuiDrawText(__boot_install_strings[8], 2, 4, WHITE);

    _ntTuiDrawText(__boot_install_strings[9], 3, 6, gray);
    _ntTuiDrawText(__boot_install_strings[10], 3, 7, gray);


    _ntTuiDrawText(__boot_install_strings[11], 6, 10, gray);

    _ntTuiDrawText(__boot_install_strings[12], 6, 12, gray);
    _ntTuiDrawText(__boot_install_strings[13], 6, 13, gray);

    _ntTuiDrawText(__boot_install_strings[14], 6, 15, gray);
}