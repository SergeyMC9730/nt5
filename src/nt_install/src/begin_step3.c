/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  Sergei Baigerov

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

    Contact Sergei Baigerov -- @dogotrigger in Discord
*/

#include <nt5emul/boot_install.h>
#include <nt5emul/renderer.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// STEP 3

// expose renderer for this step
extern void _boot_install_update_step3();
extern void _boot_install_draw_step3();

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_beginstep3() {
    _renderer_state.layers[1].on_draw.callback = _boot_install_draw_step3;
    _renderer_state.layers[1].on_update.callback = _boot_install_update_step3;

    //  NT XP License Agreement
    __state.product_name_label = __boot_install_strings[16];
    // F8=I agree  ESC=I do not agree
    __state.show_input_pointer = __boot_install_strings[18];

    // check if license exist
    if (FileExists(__boot_install_strings[17])) {
        // ntresources/license.txt
        __state.buffers[2] = LoadFileText(__boot_install_strings[17]);

        return;
    }

    // if not, allocate empty string
    __state.buffers[2] = (char *)MemAlloc(64);
}