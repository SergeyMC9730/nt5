#include <nt5emul/tui/environment.h>

extern struct nt_tui_environment _ntTuiEnvironment;

#include <string.h>

#include <nt5emul/tui/text.h>
#include <nt5emul/tui/rectangle.h>
#include <nt5emul/tui/menu.h>

void _ntUpdateMenu(struct nt_tui_menu *menu) {
    if (!menu || menu->items_total == 0) return;

    // check if KEY_DOWN is pressed
    if (IsKeyPressed(KEY_DOWN)) {
        menu->selected_item++; // increment item id

        // do boundary check
        if (menu->selected_item >= menu->items_total) {
            menu->selected_item = 0;
        }
    }

    // check if KEY_UP is pressed
    else if (IsKeyPressed(KEY_UP)) {
        menu->selected_item--; // decrement item id

        // do boundary check
        if (menu->selected_item < 0) {
            menu->selected_item = menu->items_total - 1;
        }
    }

    // check if KEY_ENTER is pressed
    else if (IsKeyPressed(KEY_ENTER)) {
        // run callback

        if (menu->click_handler != NULL) menu->click_handler(menu->selected_item, menu);
    }

    return;
}

void _ntTuiDrawMenu(struct nt_tui_menu menu) {
    int i = 0;

    while (i < menu.items_total) {
        Color text_color = menu.unselected_text_color;

        if (i == menu.selected_item) {
            Rectangle rect;

            // create rectangle
            rect.x = menu.x;
            rect.y = menu.y + i;
            rect.width = strlen(menu.objects[i]);
            rect.height = 1;

            // draw rectangle
            _ntTuiDrawRectangle(rect, menu.selected_background_color);
            
            // set text color to selected one
            text_color = menu.selected_text_color;
        }

        // draw text
        _ntTuiDrawText(menu.objects[i], menu.x, menu.y + i, text_color);

        i++; 
    }

    return;
}