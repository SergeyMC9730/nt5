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

#include <nt5emul/arrays/rsb_array_string.h>
#include <nt5emul/arrays/rsb_array_color.h>
#include <nt5emul/tui/menu.h>

enum nt_file_selector_requirement {
    FSFile, FSFolder
};

struct nt_file_selector_menu {
    // base menu
    struct nt_tui_menu base;

    const char *path;

    rsb_array_String *listing;
    
    // only allows entries with specified type (file or folder)
    enum nt_file_selector_requirement requirement;

    int items_per_page;
    int page;

    // only allows files with specified file formarts
    rsb_array_String *wanted_fileformats;
    // formatting for each file entry
    rsb_array_Color *colors;

    // callback is going to be called when user presses on allowed file entry
    void (*callback)(struct nt_file_selector_menu *menu, const char *file_path);
};

void _ntFileSelectorSetListing(struct nt_file_selector_menu *menu);
void _ntFileSelectorClick(int idx, struct nt_tui_menu *menu);

void _ntUpdateFileSelector(struct nt_file_selector_menu *menu);

struct nt_file_selector_menu *_ntLoadFileSelector(const char *path, int items_per_page);
void _ntUnloadFileSelector(struct nt_file_selector_menu *menu);