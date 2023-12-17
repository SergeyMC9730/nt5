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