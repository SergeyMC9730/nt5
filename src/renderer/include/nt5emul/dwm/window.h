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

#include <nt5emul/arrays/rsb_array_int.h>

#include <nt5emul/dwm/bool.h>

struct dwm_process {
    int pid;
};

struct dwm_window {
    struct dwm_process process;

    Vector2 position;
    Vector2 size;

    Rectangle titlebar_rect;
    
    const char *title;

    struct dwm_bool closed;
    struct dwm_bool hidden;
    struct dwm_bool filled;
    struct dwm_bool moving;

    void (*draw)(struct dwm_window *wnd, void *ctx);
    void (*upadte)(struct dwm_window *wnd, void *ctx);
};

struct dwm_window _ntCreateWindow(const char *title, Vector2 size);

void _ntDrawWindow(struct dwm_window *wnd, void *ctx);
void _ntUpdateWindow(struct dwm_window *wnd, void *ctx);
void _ntCloseWindow(struct dwm_window *wnd, void *ctx);