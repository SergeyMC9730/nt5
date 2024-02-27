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

#include <nt5emul/dwm/builder.h>

#include <cJSON.h>

void *_ntDwmCreateTemplateGui() {
    cJSON *instance = cJSON_CreateObject();

    cJSON *buttons = cJSON_AddArrayToObject(instance, "buttons");
    cJSON *menu = cJSON_AddObjectToObject(instance, "context_menu");
    cJSON *text = cJSON_AddArrayToObject(instance, "text");

    // begin buttons
    {
        struct dwm_button btn = {0};
        btn.activated.ability = true;
        btn.howered.ability = true;
        btn.text = "123";

        cJSON_AddItemToArray(buttons, _ntDwmBuilderCreateButton(btn));
    }

    // begin menu

    return instance;
}

void *_ntDwmCreateGui(struct dwm_gui_objects *ui) {
    return NULL;
}