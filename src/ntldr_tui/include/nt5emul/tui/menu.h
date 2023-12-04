#pragma once

#include <raylib.h>

struct nt_tui_menu {
    // selected item id inside menu
    int selected_item;
    // total amount of items
    unsigned char items_total;

    // callback
    void (*click_handler)(int idx, struct nt_tui_menu *menu);

    // menu object pointer
    const char **objects;

    // set color for any UNSELECTED menu object
    Color *object_colors;

    int x; // menu X;
    int y; // menu Y

    Color unselected_text_color;

    Color selected_background_color;
    Color selected_text_color;

    // additional pointer for callbacks
    void *ptr;
};

// update menu
void _ntUpdateMenu(struct nt_tui_menu *menu);

// draw text ui menu
void _ntTuiDrawMenu(struct nt_tui_menu menu);