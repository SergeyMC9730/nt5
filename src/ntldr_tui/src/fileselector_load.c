#include <nt5emul/tui/file_selector.h>
#include <stdlib.h>
#include <string.h>

struct nt_file_selector_menu *_ntLoadFileSelector(const char *path, int items_per_page) {
    struct nt_file_selector_menu *m = (struct nt_file_selector_menu *)malloc(sizeof(struct nt_file_selector_menu));

    m->base.selected_background_color = WHITE;
    m->base.selected_text_color = BLACK;
    m->base.unselected_text_color = WHITE;

    m->base.ptr = m;

    m->base.click_handler = _ntFileSelectorClick;

    char *p = malloc(strlen(path) + 1);
    strcpy(p, path);

    m->path = p;
   
    m->listing = RSBCreateArrayString();
    m->wanted_fileformats = RSBCreateArrayString();
    m->colors = RSBCreateArrayColor();

    m->want_file = true;

    m->items_per_page = items_per_page;
    m->page = 0;

    m->callback = NULL;

    _ntFileSelectorSetListing(m);

    return m;
}