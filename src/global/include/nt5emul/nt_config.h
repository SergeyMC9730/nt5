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

#pragma once

#include <stdbool.h>

struct nt_config {
    bool setup_completed;
    bool graphical_setup_completed;
    bool oobe_completed;

    const char *selected_lang;
    
    struct nt_user_config {
        const char *name;
        const char *picture_path;
        bool created;
#define NT_MAX_USERS 8
    } user[NT_MAX_USERS];
};

struct nt_config _ntGetConfig(const char *path);
void _ntSaveConfig(struct nt_config cfg, const char *path);
void _ntUnloadConfig(struct nt_config cfg);
void _ntAddUserToConfig(struct nt_config *cfg, const char *user);