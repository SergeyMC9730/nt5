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
#include <nt5emul/tui/menu.h>

#include <nt5emul/boot_install.h>

// STEP 5

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

void _boot_install_update_step5() {
    _ntUpdateMenu(&__state.menu0);

    #if BOOT_INSTALL_SKIP_TO_COPY == 1
    __state.menu0.click_handler(0, &__state.menu0);
    #endif
}
void _boot_install_draw_step5() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF}; // gray
    Color bg = (Color){0x00, 0x09, 0xAB, 0xFF}; // blue

    // draw string from third buffer
    _ntTuiDrawText(__state.buffers[3], 3, 4, gray);

    // draw menu
    _ntTuiDrawMenu(__state.menu0);
}