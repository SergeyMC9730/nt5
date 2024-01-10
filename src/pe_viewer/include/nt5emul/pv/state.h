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

#include <nt5emul/tui/file_selector.h>

#include <libpe/pe.h>

struct pe_viewer_state {
    struct nt_file_selector_menu *file_selector;

    const char *file_path;
    int sections;
    int directories;

    int directories_i;

    int page_i;
    int page_max;

    const char *current_page_name;

    pe_ctx_t file;
    pe_resources_t *file_resources;

    Vector2 tree_pos;
    Vector2 tree_current_pos;

    int tree_i;
    int tree_max;

    bool page2_init;


};

extern struct pe_viewer_state __state;