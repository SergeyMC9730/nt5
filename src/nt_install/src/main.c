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
#include <nt5emul/bi/cabinet.h>
#include <nt5emul/renderer.h>

// expose internal values

extern ntinstall_t __state; // installation state

// STEP 1

extern void _boot_install_update_step1();
extern void _boot_install_draw_step1();

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_begin() {
    // SetTargetFPS(30);

    _renderer_state.layers[1].on_draw.callback = _boot_install_draw_step1;
    _renderer_state.layers[1].on_update.callback = _boot_install_update_step1;

    _renderer_state.layers[2].on_update.callback = _boot_install_shortcuts_update;
    
    __state.buffers[0] = (char *)MemAlloc(32);

    __state.show_input_pointer = true;

    // init background
    _boot_install_backgroundInit();

    // init cabinet information

    _boot_install_create_cab_files();
}