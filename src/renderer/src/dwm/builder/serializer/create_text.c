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

// returns cjson handle
void *_ntDwmBuilderCreateText(struct dwm_gui_text *text) {
    cJSON *instance = cJSON_CreateObject();

    cJSON *font = cJSON_AddObjectToObject(instance, "font");

    cJSON_AddNumberToObject(font, "xp_size", text->font.xp_size);
    cJSON_AddNumberToObject(font, "real_size", text->font.real_size);
    cJSON_AddNumberToObject(font, "spacing", text->font.spacing);
    cJSON_AddStringToObject(font, "path", text->font.path);

    cJSON *position = cJSON_AddArrayToObject(instance, "position");
    cJSON_AddItemToArray(position, cJSON_CreateNumber(text->position.x));
    cJSON_AddItemToArray(position, cJSON_CreateNumber(text->position.y));

    cJSON_AddNumberToObject(instance, "scale", text->scale);
    
    return instance;
}