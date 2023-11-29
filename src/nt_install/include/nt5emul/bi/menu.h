#pragma once

typedef struct bi_menu_t {
    // selected item id inside menu
    int selected_item;
    // total amount of items
    unsigned char items_total;

    // callback
    void (*click_handler)(int idx, struct bi_menu_t *menu);

    // menu object pointer
    const char **objects;

    int x; // menu X;
    int y; // menu Y
} bi_menu_t;

void _biUpdateMenu(bi_menu_t *menu);
void _biDrawMenu(bi_menu_t menu);