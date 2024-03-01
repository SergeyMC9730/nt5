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
void * _ntDwmBuilderCreateImage(struct dwm_gui_image image) {
    cJSON *img = cJSON_CreateObject();

    cJSON *pos = cJSON_AddArrayToObject(img, "position");
    cJSON_AddItemToArray(pos, cJSON_CreateNumber(image.position.x));
    cJSON_AddItemToArray(pos, cJSON_CreateNumber(image.position.y));

    cJSON_AddStringToObject(img, "path", image.path);
    
    cJSON_AddNumberToObject(img, "scale", image.scale);

    return img;
}