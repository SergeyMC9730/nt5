/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  SergeyMC9730

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

    Contact SergeyMC9730 -- @dogotrigger in Discord
*/

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

    else if (IsKeyPressed(KEY_PAGE_DOWN)) {
        menu->selected_item += menu->items_total / 2;

        if (menu->selected_item >= menu->items_total) {
            menu->selected_item = menu->items_total - 1;
        }
    }

    else if (IsKeyPressed(KEY_PAGE_UP)) {
        menu->selected_item -= menu->items_total / 2;

        // do boundary check
        if (menu->selected_item < 0) {
            menu->selected_item = 0;
        }
    }

    return;
}

void _ntTuiDrawMenu(struct nt_tui_menu menu) {
    int i = 0;

    while (i < menu.items_total) {
        Color text_color = menu.unselected_text_color;

        if (menu.object_colors != NULL) {
            Color c = menu.object_colors[i];

            if (c.a == 0xFF) text_color = c; 
        }

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