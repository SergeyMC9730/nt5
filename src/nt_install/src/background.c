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

#include <nt5emul/boot_install.h>

#include <string.h>
#include <stdio.h>

#include <nt5emul/tui/text.h>
#include <nt5emul/tui/rectangle.h>

#include <nt5emul/renderer.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

void _biDrawBackgroundEx(const char *product_name, const char *help_shortcuts, Color bg_color, Color status_color, Color status_text_color) {    
    if (__state.buffers[0] == NULL) return;
    
    renderer_state_t *st = _ntRendererGetState();
    
    int window_size_x = st->current_window_size.x / __state.base_size.x; // get x size in characters
    int window_size_y = st->current_window_size.y / __state.base_size.y; // get y size in characters
    
    // clear background
    ClearBackground(bg_color);
    
    int l = -3; // product name length

    // check if product name exists and do processing of it
    if (product_name != NULL) {
        _ntTuiDrawText(product_name, 0, 1, status_color);

        // get length of product name
        l = strlen(product_name) + 1;

        // draw line below product name
        for (unsigned int i = 0; i < l; i++) {
            // ═
            _ntTuiDrawText(__boot_install_strings[2], i, 2, status_color);
        }
    }

    // format fps string
    snprintf(__state.buffers[0], 32, __boot_install_strings[3], (1.f / GetFrameTime()));

    /*
        draw fps

        if product name doesn't exist we can 
        just  set  its  length  to -3  and X 
        position  for  fps label  would be 0
    */
    _ntTuiDrawText(__state.buffers[0], l + 3, 2, GRAY);

    // check if help shortcuts exists and do processing of it
    if (help_shortcuts != NULL) {
        // draw status background
        _ntTuiDrawRectangle((Rectangle){0, window_size_y - 1, window_size_x, 1}, status_color);

        // draw help shortcuts
        _ntTuiDrawText(help_shortcuts, 2, window_size_y - 1, status_text_color);
    }
}

void _biDrawBackground(const char *product_name, const char *help_shortcuts) {
    return _biDrawBackgroundEx(
        product_name,
        help_shortcuts, 
        (Color){0x00, 0x09, 0xAB, 0xFF}, // blue background
        (Color){0xA8, 0xA8, 0xA8, 0xFF}, // gray status bar
        BLACK
    );
}