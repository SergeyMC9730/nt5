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

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>
#include <nt5emul/bi/xp_detection.h>

#include <stdio.h>
#include <string.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// STEP 6

extern void _boot_install_update_step6();
extern void _boot_install_draw_step6();

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_beginstep6(int idx, struct nt_tui_menu *menu) {
    __state.selected_format_option = idx;

    if (idx >= 2) {
        __state.timer0_max = 3.f;
    } else {
        __state.timer0_max = 1.f;
    }

    _renderer_state.layers[1].on_update.callback = _boot_install_update_step6;
    _renderer_state.layers[1].on_draw.callback = _boot_install_draw_step6;

    // reallocate and fill buffer 3 with zeros
    __state.buffers[3] = MemRealloc(__state.buffers[3], 64);
    memset(__state.buffers[3], 0, 64);

    _boot_install_detect_xp();

    if (__state.buffers[3][0] == 0) {
        __state.detection_required = true;

        _boot_install_detect_xp();
    }
}