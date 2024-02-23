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

#include <raylib.h>

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

// expose internal values

extern ntinstall_t __state; // installation state

// expose NT renderer
extern renderer_state_t _renderer_state;

#ifndef NULL
#define NULL ((void *)0)
#endif

void _boot_install_backgroundInit() {
    _renderer_state.layers[0].on_draw.callback = _boot_install_drawBackground;
    _renderer_state.layers[0].on_update.callback = NULL;
}

void _boot_install_drawBackground() {
    if (__state.halt) return;

    Color blue = (Color){0x00, 0x09, 0xAB, 0xFF};

    const char *status = (__state.status_bar_is_error) ? __state.status_bar_error :  __state.status_bar_label;

    if (!__state.status_bar_is_error) {
        _biDrawBackground(__state.product_name_label, status);
    } else {
        _biDrawBackgroundEx(__state.product_name_label, status, blue, RED, WHITE);
    }
}