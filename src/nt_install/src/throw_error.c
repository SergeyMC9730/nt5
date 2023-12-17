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
#include <nt5emul/timer.h>

// expose internal values

extern ntinstall_t __state; // installation state

void _boot_install_throw_error_end() {
    __state.status_bar_is_error = false;
}

void _boot_install_throw_error(const char *error) {
    if (__state.status_bar_is_error) return;
    
    __state.status_bar_is_error = true;
    __state.status_bar_error = error;

    _ntInstallTimer(_boot_install_throw_error_end, 0.5f);
}