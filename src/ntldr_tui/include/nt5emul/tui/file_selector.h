#pragma once

#include "../../../arrays/include/nt5emul/arrays/rsb_array_string.h"
#include <nt5emul/tui/menu.h>

struct nt_file_selector_menu {
    // base menu
    struct nt_tui_menu base;

    const char *path;

    rsb_array_String *listing;
    
    // false - want folder
    // true  - want file
    bool want_file;

    int items_per_page;
    int page;

    void (*callback)(struct nt_file_selector_menu *menu, const char *file_path);
};

void _ntFileSelectorSetListing(struct nt_file_selector_menu *menu);
void _ntFileSelectorClick(int idx, struct nt_tui_menu *menu);

void _ntUpdateFileSelector(struct nt_file_selector_menu *menu);

struct nt_file_selector_menu *_ntLoadFileSelector(const char *path, int items_per_page);
void _ntUnloadFileSelector(struct nt_file_selector_menu *menu);