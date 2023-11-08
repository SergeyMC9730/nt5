#pragma once

typedef struct bi_menu_t {
    int selected_item;
    unsigned char items_total;

    void (*click_handler)(int idx, struct bi_menu_t *menu);

    const char **objects;

    int x;
    int y;
} bi_menu_t;

void _biUpdateMenu(bi_menu_t *menu);
void _biDrawMenu(bi_menu_t menu);