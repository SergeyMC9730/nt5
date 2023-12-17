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
#include <nt5emul/directory_exists.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void _ntFileSelectorClick(int idx, struct nt_tui_menu *menu) {
    // get file selector
    struct nt_file_selector_menu *m = (struct nt_file_selector_menu *)menu->ptr;
    
    // get selected string
    const char *obj = RSBGetAtIndexString(m->listing, idx);

    // check if string is "[ NEXT PAGE ]"
    if (!strcmp(obj, "[ NEXT PAGE ]")) {
        // increment page index
        m->page++;

        // update listing
        _ntFileSelectorSetListing(m);

        return;
    // check if string is "[ PREV PAGE ]"
    } else if (!strcmp(obj, "[ PREV PAGE ]")) {
        // decrement page
        m->page--;

        // update listing
        _ntFileSelectorSetListing(m);

        return;
    }

    // get string length
    size_t basefile = strlen(obj);

    // get path string length
    size_t basepath = strlen(m->path);
    
    // check if last character is '>'
    if (obj[basefile - 1] == '>') {
        // remove it along side with ' '
        ((char *)obj)[basefile - 2] = 0;
    }

    // get full string length
    size_t l1 = strlen(m->path) + strlen(obj) + 4;

    // allocate filepath with this length
    char *filepath = malloc(l1);

    // format string
    snprintf(filepath, l1, "%s/%s", m->path, obj);

    // printf("path: %s (is dir %d; is file %d)\n", filepath, _ntDirectoryExist(filepath), !_ntDirectoryExist(filepath));

    // check if directory <filepath> exists
    if (_ntDirectoryExists(filepath)) {
        // check if we want file
        if (m->want_file) {
            // free path string memory
            free((char *)m->path);

            // set new path
            m->path = filepath;

            // set current page to 0
            m->page = 0;

            // update listing
            _ntFileSelectorSetListing(m);
        } else {
            // check if callback exists
            if (m->callback != NULL) {
                // call function
                m->callback(m, filepath);
                
                // free filepath memory
                free(filepath);
            }
        }
    } else {
        // check if we want file and callback can be used
        if (m->want_file && m->callback != NULL) {
            // call function
            m->callback(m, filepath);

            // free filepath memory
            free(filepath);
        }
    }
}