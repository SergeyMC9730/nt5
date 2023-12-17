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

#include <nt5emul/tui/menu.h>

#include <nt5emul/bi/cabfile.h>

#include <stddef.h>

typedef struct ntinstall_t {
    Font font;
    Vector2 base_size;

    char *buffers[16];

    // menu related variables
    unsigned char idx0;
    struct nt_tui_menu menu0;

    bool show_input_pointer;

    unsigned char selected_format_option;

    bool status_bar_is_error;
    const char *status_bar_error;

    const char *product_name_label;
    const char *status_bar_label;

    float timer0;
    float timer0_max;

    int timer1;

    rsb_array_cabfile *cabfile_list;
    const char *cabfile_current_file;
    int max_cabfile_length;

    bool detection_required;

    bool halt;
} ntinstall_t;