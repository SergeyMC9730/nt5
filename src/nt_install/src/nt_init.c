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

#include <nt5emul/tui/text.h>
#include <nt5emul/renderer.h>
#include <nt5emul/nt_install.h>
#include <nt5emul/boot_install_settings.h>
#include <nt5emul/timer.h>
#include <nt5emul/boot_install_steps.h>

#include <nt5emul/nt_config.h>

#include <cJSON.h>
#include <stdio.h>
// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_create_config() {
    struct nt_config config = _ntGetConfig("nt/config.json");

    config.setup_completed = true;

    _ntSaveConfig(config, "nt/config.json");

    _ntUnloadConfig(config);
}

void _boot_install_step9_config() {
    _boot_install_create_config();

    _boot_install_beginstep10();
}

void _boot_install_update_step9() {
    _ntInstallTimer(_boot_install_step9_config, 0.3f, NULL);

    _renderer_state.layers[1].on_update.callback = NULL;
}

void _boot_install_draw_step9() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};

    // Please wait while Setup initializes your NT XP configuration.
    _ntTuiDrawTextCentered(__boot_install_strings[51], 0xFF, 7, gray);
}