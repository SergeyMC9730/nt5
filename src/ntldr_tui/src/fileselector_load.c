/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  SergeyMC9730

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

    Contact SergeyMC9730 -- @dogotrigger in Discord
*/

#include <nt5emul/tui/file_selector.h>
#include <stdlib.h>
#include <string.h>

struct nt_file_selector_menu *_ntLoadFileSelector(const char *path, int items_per_page) {
    // allocate file selector
    struct nt_file_selector_menu *m = (struct nt_file_selector_menu *)malloc(sizeof(struct nt_file_selector_menu));
    
    // setup colors
    m->base.selected_background_color = WHITE;
    m->base.selected_text_color = BLACK;
    m->base.unselected_text_color = WHITE;

    // set base pointer to this
    m->base.ptr = m;
    
    // set click handler for the base structure
    m->base.click_handler = _ntFileSelectorClick;
    
    // allocate path memory
    char *p = malloc(strlen(path) + 1);
    // copy string
    strcpy(p, path);

    m->path = p;
    
    // create listing array
    m->listing = RSBCreateArrayString();
    // create file format requirements array
    m->wanted_fileformats = RSBCreateArrayString();
    // create color array
    m->colors = RSBCreateArrayColor();

    m->want_file = true;

    m->items_per_page = items_per_page;
    m->page = 0;

    m->callback = NULL;

    // update file listing
    _ntFileSelectorSetListing(m);

    return m;
}