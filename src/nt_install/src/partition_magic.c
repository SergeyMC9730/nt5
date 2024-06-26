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

#include <nt5emul/tui/text.h>
#include <nt5emul/tui/frame.h>

#include <stdio.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// STEP 4

void _boot_install_update_step4() {
    if (IsKeyPressed(KEY_C)) {
        // Cannot load Create Partition routine: Not Implemented
        _boot_install_throw_error(__boot_install_strings[45]);
    }

    _ntUpdateMenu(&__state.menu0);

    #if BOOT_INSTALL_SKIP_TO_COPY == 1
    __state.menu0.click_handler(0, &__state.menu0);
    #endif
}
void _boot_install_draw_step4() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};
    Color bg = (Color){0x00, 0x09, 0xAB, 0xFF};

    // partition tutorial string
    _ntTuiDrawText(__boot_install_strings[19], 3, 4, gray);

    _ntTuiDrawMenu(__state.menu0);

    // %d MB Disk %d at Id %d on bus %d on atapi [MBR]
    snprintf(__state.buffers[4], 256, __boot_install_strings[20], 16 * 1024, __state.menu0.selected_item, 0, 0);

    renderer_state_t *st = _ntRendererGetState();

    // get render width in characters
    int szX = st->current_window_size.x / __state.base_size.x;

    _ntTuiDrawFrame((Rectangle){2, 14, szX - 5, 13}, gray, __state.buffers[4]);
}
