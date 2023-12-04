#include <nt5emul/tui/file_selector.h>
#include <nt5emul/directory_exist.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void _ntFileSelectorClick(int idx, struct nt_tui_menu *menu) {

    struct nt_file_selector_menu *m = (struct nt_file_selector_menu *)menu->ptr;

    const char *obj = RSBGetAtIndexString(m->listing, idx);

    if (!strcmp(obj, "[ NEXT PAGE ]")) {
        m->page++;

        _ntFileSelectorSetListing(m);

        return;
    } else if (!strcmp(obj, "[ PREV PAGE ]")) {
        m->page--;

        _ntFileSelectorSetListing(m);

        return;
    }

    size_t basefile = strlen(obj);
    size_t basepath = strlen(m->path);

    if (obj[basefile - 1] == '>') {
        ((char *)obj)[basefile - 2] = 0;
    } 

    size_t l1 = strlen(m->path) + strlen(obj) + 4;

    char *filepath = malloc(l1);

    snprintf(filepath, l1, "%s/%s", m->path, obj);

    printf("path: %s (is dir %d; is file %d)\n", filepath, _ntDirectoryExist(filepath), !_ntDirectoryExist(filepath));

    if (_ntDirectoryExist(filepath)) {
        if (m->want_file) {
            free((char *)m->path);
            m->path = filepath;

            m->page = 0;

            _ntFileSelectorSetListing(m);
        } else {
            if (m->callback != NULL) {
                m->callback(m, filepath);

                free(filepath);
            }
        }
    } else {
        if (m->want_file && m->callback != NULL) {
            m->callback(m, filepath);

            free(filepath);
        }
    }
}