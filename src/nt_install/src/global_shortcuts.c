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
#include <nt5emul/ntcore.h>
#include <nt5emul/boot_install_settings.h>

#include <raylib.h>

#include <stdio.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings

void _boot_install_shortcuts_update() {
    if (IsKeyPressed(KEY_F9)) {
        puts(__boot_install_strings[37]); // F9 Info:

        const char *s_busy = __boot_install_strings[39]; // busy
        const char *s_free = __boot_install_strings[40]; // free

        for (size_t i = 0; i < 16; i++) {
            // check if core is busy or not
            bool busy = _ntCoreBusy(i);
            
            //  * C%zu - %s
            printf(__boot_install_strings[38], i, busy ? s_busy : s_free);
        }
    }
}