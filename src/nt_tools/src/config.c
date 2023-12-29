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

#include <cJSON.h>

#include <stdio.h>
#include <stdlib.h>

struct nt_config _ntGetConfig(const char *path) {
    struct nt_config config = {};

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
    
    if (setup_completed && cJSON_IsBool(setup_completed)) {
        config.setup_completed = setup_completed->valueint;
    }

    if (oobe_completed && cJSON_IsBool(oobe_completed)) {
        config.oobe_completed = oobe_completed->valueint;
    }

    if (graphical_setup_completed && cJSON_IsBool(graphical_setup_completed)) {
        config.graphical_setup_completed = graphical_setup_completed->valueint;
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

    char *cfgstr = cJSON_Print(config_object); 

    FILE *cfgfile = fopen(path, "w");
    
    if (!cfgfile) goto end;

    fputs(cfgstr, cfgfile); 
end:
    cJSON_free(cfgstr); 
    cJSON_Delete(config_object);

    if (cfgfile != NULL) fclose(cfgfile); 
}