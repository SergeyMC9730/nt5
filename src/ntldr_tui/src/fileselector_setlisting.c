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

#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include <nt5emul/tui/file_selector.h>
#include <nt5emul/directory_exists.h>

void _ntFileSelectorSetListing(struct nt_file_selector_menu *m) {
    DIR *d = opendir(m->path);
    struct dirent *dir;

    if (d) {
        size_t i = 0;

        while (i < m->listing->len) {
            const char *str = RSBGetAtIndexString(m->listing, i);
            free((char *)str);

            i++;
        }

        i = 0;

        while (m->listing->len != 0) {
            RSBPopElementString(m->listing);
        }
        while (m->colors->len != 0) {
            RSBPopElementColor(m->colors);
        }

        int has_prev = 0;

        if (m->page >= 1) {
            char *prev_page_str = "[ PREV PAGE ]";

            size_t l = strlen(prev_page_str) + 1;

            char *prev_page = (char *)malloc(l);

            memset(prev_page, 0, l);

            strncpy(prev_page, prev_page_str, l - 1);

            RSBAddElementString(m->listing, prev_page);

            Color c = YELLOW;
            RSBAddElementColor(m->colors, c);

            has_prev = 1;
        }

        int pg_index_max = m->items_per_page * (m->page + 1);

        while (((dir = readdir(d)) != NULL) && i < pg_index_max) {
            if (i < (m->page * m->items_per_page)) {
                i++;

                continue;
            }

            const char *str_r = dir->d_name;

            size_t l = strlen(str_r) + 3;

            char *str_a = (char *)malloc(l);

            const char *folder_open = " >";

            // printf(" * path: %s")

            size_t l1 = strlen(dir->d_name) + strlen(m->path) + 2;

            char *bf = (char *)malloc(l1);

            snprintf(bf, l1, "%s/%s", m->path, dir->d_name);

            Color c = m->base.unselected_text_color;

            if (!_ntDirectoryExists(bf)) {
                folder_open = "";

                if (m->requirement == FSFile) {
                    for (size_t j = 0; j < m->wanted_fileformats->len; j++) {
                        const char *req = RSBGetAtIndexString(m->wanted_fileformats, j);

                        if (IsFileExtension(bf, req)) {
                            c = GREEN;
                        }
                    }
                }
            }

            free(bf);

            snprintf(str_a, l, "%s%s", str_r, folder_open);

            RSBAddElementString(m->listing, (const char *)str_a);
            RSBAddElementColor(m->colors, c);

            i++;
        }

        if (m->listing->len == (m->items_per_page + has_prev)) {
            char *next_page_str = "[ NEXT PAGE ]";

            size_t l = strlen(next_page_str) + 1;

            char *next_page = (char *)malloc(l);

            memset(next_page, 0, l);

            strncpy(next_page, next_page_str, l - 1);

            Color c = YELLOW;

            RSBAddElementString(m->listing, next_page);
            RSBAddElementColor(m->colors, c);
        }

        closedir(d);

        m->base.selected_item = 0;
    }

    m->base.items_total = m->listing->len;
    m->base.objects = m->listing->objects;
    m->base.object_colors = m->colors->objects;
}