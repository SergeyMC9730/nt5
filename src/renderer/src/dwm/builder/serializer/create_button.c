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

void * _ntDwmBuilderCreateButton(struct dwm_button btn) {
    cJSON *button = cJSON_CreateObject();

    cJSON *rect = cJSON_AddArrayToObject(button, "rect");

    cJSON_AddItemToArray(rect, cJSON_CreateNumber(btn.button.x));
    cJSON_AddItemToArray(rect, cJSON_CreateNumber(btn.button.y));
    cJSON_AddItemToArray(rect, cJSON_CreateNumber(btn.button.width));
    cJSON_AddItemToArray(rect, cJSON_CreateNumber(btn.button.height));
    
    cJSON_AddStringToObject(button, "text", btn.text);

    cJSON *texture = cJSON_AddObjectToObject(button, "texture");
    cJSON_AddStringToObject(texture, "off", "");
    cJSON_AddStringToObject(texture, "on", "");

    cJSON_AddBoolToObject(button, "can_activate", btn.activated.ability);
    cJSON_AddBoolToObject(button, "can_hower", btn.howered.ability);
    cJSON_AddBoolToObject(button, "dark", btn.dark.ability);

    cJSON_AddNumberToObject(button, "id", btn.id);

    return button;
}