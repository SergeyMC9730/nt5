/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  Sergei Baigerov

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

    Contact Sergei Baigerov -- @dogotrigger in Discord
*/

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <stdio.h>
#include <string.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// STEP 4

// expose renderer for this state
extern void _boot_install_update_step4();
extern void _boot_install_draw_step4();

char *__boot_install_objects00[1] = {0};

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_beginstep4() {
    // allocate two buffers
    __state.buffers[3] = MemAlloc(256);
    __state.buffers[4] = MemAlloc(256);

    const char *s1 = __boot_install_strings[21]; // Unpartitioned space

    // format string
    snprintf(__state.buffers[3], 256, "     %s               %d MB", s1, 16 * 1024);

    renderer_state_t *st = _ntRendererGetState();

    // get Render width in characters
    int szX = st->current_window_size.x / __state.base_size.x; // 8
    int szY = st->current_window_size.y / __state.base_size.y; // 16

    // check occupied space by this string 
    // and   process   math   calculations  
    size_t occupied_space = strlen(__state.buffers[3]);
    int spaces = szX - occupied_space - 12;
    int i = 0;

    // bi_menu would highlight an entire string
    // include    any     empty     characters.
    while (i < spaces) {
        strcat(__state.buffers[4], " ");
        i++;
    }

    // add two strings
    strcat(__state.buffers[3], __state.buffers[4]);

    __boot_install_objects00[0] = __state.buffers[3];

    // gray color
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};
    // blue color
    Color bg = (Color){0x00, 0x09, 0xAB, 0xFF};

    // create bi_menu
    __state.menu0.items_total = 1;
    __state.menu0.objects = (const char **)__boot_install_objects00;
    __state.menu0.click_handler = _boot_install_beginstep5;
    __state.menu0.y = 17;
    __state.menu0.x = 5;
    __state.menu0.unselected_text_color = gray;
    __state.menu0.selected_text_color = bg;
    __state.menu0.selected_background_color = gray;

    _renderer_state.layers[1].on_draw.callback = _boot_install_draw_step4;
    _renderer_state.layers[1].on_update.callback = _boot_install_update_step4;

    //  NT Professional Setup
    __state.product_name_label = __boot_install_strings[7];
    // ENTER=Install  C=Create Partition  F3=Quit
    __state.status_bar_label = __boot_install_strings[23];
}