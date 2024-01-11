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

#include <nt5emul/nt_config.h>
#include <nt5emul/file_exists.h>
#include <nt5emul/read_text.h>
#include <nt5emul/copy_string.h>

#include <cJSON.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nt_config _ntGetConfig(const char *path) {
    struct nt_config config = {
        .selected_lang = "en"
    };
    
    if (!_ntFileExists(path)) {
        printf("config doesn't exist\n");
        return config;
    }

    char *data = (char *)_ntReadTextFile(path);

    if (!data) return config;

    cJSON *config_object = cJSON_Parse(data);
    if (!config_object) {
        free(data);

        return config;
    }

    cJSON *setup_completed = cJSON_GetObjectItem(config_object, "setup_completed");
    cJSON *oobe_completed = cJSON_GetObjectItem(config_object, "oobe_completed");
    cJSON *graphical_setup_completed = cJSON_GetObjectItem(config_object, "graphical_setup_completed");
    cJSON *selected_lang = cJSON_GetObjectItem(config_object, "selected_lang");
    
    if (setup_completed && cJSON_IsBool(setup_completed)) {
        config.setup_completed = setup_completed->valueint;
    }

    if (oobe_completed && cJSON_IsBool(oobe_completed)) {
        config.oobe_completed = oobe_completed->valueint;
    }

    if (graphical_setup_completed && cJSON_IsBool(graphical_setup_completed)) {
        config.graphical_setup_completed = graphical_setup_completed->valueint;
    }

    if (selected_lang && cJSON_IsString(selected_lang)) {
        if (!strcmp(selected_lang->valuestring, "ru")) {
            config.selected_lang = "ru";
        }
    }

    cJSON *user_array = cJSON_GetObjectItem(config_object, "users");

    if (user_array && cJSON_IsArray(user_array)) {
        cJSON *user_object = NULL;
        int user_index = 0;

        // go through each created user
        cJSON_ArrayForEach(user_object, user_array) {
            if (user_index == NT_MAX_USERS) break;

            if (cJSON_IsObject(user_object)) {
                cJSON *name_object = cJSON_GetObjectItem(user_object, "name");
                cJSON *picture_object = cJSON_GetObjectItem(user_object, "picture_path");
                cJSON *created_object = cJSON_GetObjectItem(user_object, "created");

                if (name_object && cJSON_IsString(name_object)) {
                    config.user[user_index].name = (const char *)_ntCopyString(name_object->valuestring);
                }
                if (picture_object && cJSON_IsString(picture_object)) {
                    config.user[user_index].picture_path = (const char *)_ntCopyString(picture_object->valuestring);
                }
                
                if (created_object && cJSON_IsBool(created_object)) {
                    config.user[user_index].created = created_object->valueint;
                }
            }
            
            user_index++;
        }
    } else {
        // without users you would not be able to go further than logonui
        config.oobe_completed = false;
    }

    cJSON_Delete(config_object);
    free(data);

    return config;
}

void _ntSaveConfig(struct nt_config cfg, const char *path) {
    cJSON *config_object = cJSON_CreateObject();

    cJSON_AddBoolToObject(config_object, "setup_completed", cfg.setup_completed);
    cJSON_AddBoolToObject(config_object, "oobe_completed", cfg.oobe_completed);
    cJSON_AddBoolToObject(config_object, "graphical_setup_completed", cfg.graphical_setup_completed);

    cJSON_AddStringToObject(config_object, "selected_lang", cfg.selected_lang);

    cJSON *user_array = cJSON_AddArrayToObject(config_object, "users");

    for (int i = 0; i < NT_MAX_USERS; i++) {
        if (cfg.user[i].created) {
            cJSON *user_object = cJSON_CreateObject();

            cJSON_AddBoolToObject(user_object, "created", cfg.user[i].created);

            cJSON_AddStringToObject(user_object, "name", cfg.user[i].name);
            cJSON_AddStringToObject(user_object, "picture_path", cfg.user[i].picture_path);

            cJSON_AddItemToArray(user_array, user_object);
        }
    }

    char *cfgstr = cJSON_Print(config_object); 

    FILE *cfgfile = fopen(path, "w");
    
    if (!cfgfile) goto end;

    fputs(cfgstr, cfgfile); 
end:
    cJSON_free(cfgstr); 
    cJSON_Delete(config_object);

    if (cfgfile != NULL) fclose(cfgfile); 
}

void _ntUnloadConfig(struct nt_config cfg) {
    for (int i = 0; i < NT_MAX_USERS; i++) {
        if (cfg.user[i].name) {
            free((char *)cfg.user[i].name);
            free((char *)cfg.user[i].picture_path);
        }
    }
}

void _ntAddUserToConfig(struct nt_config *cfg, const char *user) {
    for (int i = 0; i < NT_MAX_USERS; i++) {
        if (!cfg->user[i].created) {
            cfg->user[i].name = _ntCopyString(user);
            cfg->user[i].picture_path = _ntCopyString("nt/images/user/avatars/airplane.bmp");
            cfg->user[i].created = true;

            return;
        }
    }
}