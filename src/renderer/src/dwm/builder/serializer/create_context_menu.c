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

void *_ntDwmBuilderCreateContextMenu(struct dwm_context_menu *menu) {
    cJSON *m = cJSON_CreateObject();

    cJSON *m1 = cJSON_AddArrayToObject(m, "buttons");

    for (int i = 0; i < 8; i++) {
        struct dwm_context_menu_button *_btn = menu->buttons + i;

        if (!_btn->used) continue;
        
        cJSON *btn = cJSON_CreateObject();
        
        cJSON_AddItemToObject(btn, _ntDwmBuilderCreateButton(_btn->base), "base");

        cJSON *section_array = cJSON_AddArrayToObject(btn, "sections");

        for (int j = 0; j < 4; j++) {
            struct dwm_context_menu_selector_section *_section = _btn->sections + i;

            if (!_section->used) continue;

            cJSON *section = cJSON_CreateObject();

            cJSON *field_array = cJSON_AddArrayToObject(section, "fields");

            for (int k = 0; k < 8; k++) {
                struct dwm_context_menu_selector *_field = _section->fields + i;

                if (!_field->used) continue;

                cJSON *field = cJSON_CreateObject();

                cJSON_AddBoolToObject(field, "disabled", _field->disabled);
                cJSON_AddNumberToObject(field, "id", _field->id);
                cJSON_AddStringToObject(field, "content", _field->content);

                const char *k1 = _ntDwmTranslateKeyToStr(_field->key_shortcut[0]);
                const char *k2 = _ntDwmTranslateKeyToStr(_field->key_shortcut[1]);

                cJSON *key_shortcuts = cJSON_AddArrayToObject(field, "shortcut");
                cJSON *_k1 = cJSON_CreateString(k1);
                cJSON *_k2 = cJSON_CreateString(k2);
                cJSON_AddItemToArray(key_shortcuts, _k1);
                cJSON_AddItemToArray(key_shortcuts, _k2);

                cJSON_AddItemToArray(field_array, field);
            }

            cJSON_AddItemToArray(section_array, section);
        }

        cJSON_AddItemToArray(m1, btn);
    }

    return m;
}