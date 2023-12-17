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

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <string.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// STEP 7

extern void _boot_install_update_step7();
extern void _boot_install_draw_step7();

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_beginstep7() {
    _renderer_state.layers[1].update = _boot_install_update_step7;
    _renderer_state.layers[1].draw = _boot_install_draw_step7;

    // allocate buffer 7
    __state.buffers[7] = MemAlloc(64);
    // reset buffer 7
    memset(__state.buffers[7], 0, 64);
    // copy input from user to buffer 7
    strncpy(__state.buffers[7], __state.buffers[3], 64);

    // reset buffer 3
    memset(__state.buffers[3], 0, 64);

    __state.status_bar_label = "";

    __state.detection_required = false;
}