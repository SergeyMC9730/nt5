#include <nt5emul/boot_install.h>

#include <string.h>

#include <nt5emul/bi/text.h>
#include <nt5emul/bi/rectangle.h>

void _biUpdateMenu(bi_menu_t *menu) {
    if (!menu || menu->items_total == 0) return;

    if (IsKeyPressed(KEY_DOWN)) {
        menu->selected_item++;

        if (menu->selected_item >= menu->items_total) {
            menu->selected_item = 0;
        }
    }
    if (IsKeyPressed(KEY_UP)) {
        menu->selected_item--;

        if (menu->selected_item < 0) {
            menu->selected_item = menu->items_total - 1;
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        menu->click_handler(menu->selected_item, menu);
    }

    return;
}

void _biDrawMenu(bi_menu_t menu) {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};
    Color bg = (Color){0x00, 0x09, 0xAB, 0xFF};

    int i = 0;

    while (i < menu.items_total) {
        Color text_color = gray;

        if (i == menu.selected_item) {
            Rectangle rect;

            rect.x = menu.x;
            rect.y = menu.y + i;
            rect.width = strlen(menu.objects[i]);
            rect.height = 1;

            _biRectangleDraw(rect, gray);
            
            text_color = bg;
        }

        _biTextDraw(menu.objects[i], menu.x, menu.y + i, text_color);

        i++; 
    }

    return;
}