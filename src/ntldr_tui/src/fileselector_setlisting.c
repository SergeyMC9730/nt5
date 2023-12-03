#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include <nt5emul/tui/file_selector.h>

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

            i++;
        }

        i = 0;

        int has_prev = 0;

        if (m->page >= 1) {
            char *prev_page_str = "[ PREV PAGE ]";

            size_t l = strlen(prev_page_str) + 1;

            char *prev_page = (char *)malloc(l);

            memset(prev_page, 0, l);

            strncpy(prev_page, prev_page_str, l - 1);

            RSBAddElementString(m->listing, prev_page);

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

            if (!DirectoryExists(dir->d_name)) {
                folder_open = "";
            }

            snprintf(str_a, l, "%s%s", str_r, folder_open);

            RSBAddElementString(m->listing, (const char *)str_a);

            i++;
        }

        if (m->listing->len == (m->items_per_page + has_prev)) {
            char *next_page_str = "[ NEXT PAGE ]";

            size_t l = strlen(next_page_str) + 1;

            char *next_page = (char *)malloc(l);

            memset(next_page, 0, l);

            strncpy(next_page, next_page_str, l - 1);

            RSBAddElementString(m->listing, next_page);
        }

        closedir(d);

        m->base.selected_item = 0;
    }

    m->base.items_total = m->listing->len;
    m->base.objects = m->listing->objects;
}