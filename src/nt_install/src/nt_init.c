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
#include <nt5emul/renderer.h>
#include <nt5emul/nt_install.h>
#include <nt5emul/boot_install_settings.h>
#include <nt5emul/timer.h>
#include <nt5emul/boot_install_steps.h>

#include <cJSON.h>
#include <stdio.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_create_config() {
    // create json object
    cJSON *j = cJSON_CreateObject();
    cJSON *setup_completed = cJSON_CreateBool(false);

    cJSON_AddItemToObject(j, "setup_completed", setup_completed);

    // convert json object into a string
    char *str = cJSON_Print(j);

    // open config.json stream
    FILE *fp = fopen("nt/config.json", "w");

    // write json object
    fputs(str, fp);
    fclose(fp);

    // destroy json object;
    cJSON_free(str);
    cJSON_Delete(j);
}

void _boot_install_step9_config() {
    _boot_install_create_config();

    _boot_install_beginstep10();
}

void _boot_install_update_step9() {
    _ntInstallTimer(_boot_install_step9_config, 1.f / (float)GetFPS());

    _renderer_state.layers[1].update = NULL;
}

void _boot_install_draw_step9() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};

    // Please wait while Setup initializes your NT XP configuration.
    _ntTuiDrawTextCentered(__boot_install_strings[51], 0xFF, 7, gray);
}