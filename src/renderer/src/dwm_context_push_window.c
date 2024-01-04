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

#include <nt5emul/dwm/context.h>

#include <string.h>

#include <stdio.h>

// push window to the dwm context
void _ntPushWindow(struct dwm_context *ctx, struct dwm_window wnd) {
    struct dwm_window wnd2 = wnd;

    // set process id
    wnd2.process.pid = ++ctx->global_process_increment;
    wnd2.moving.ability = true;

    // add window to the window array
    RSBAddElementDWMWindow(ctx->windows, wnd2);
    struct dwm_window *wnd_ptr = ctx->windows->objects + (ctx->windows->current_index - 1);

    // make it selected
    ctx->selected_window = wnd_ptr;

    printf("window %d with pos %f:%f; size %f:%f\n",wnd2.process.pid, wnd2.position.x, wnd2.position.y, wnd2.size.x, wnd2.size.y);
}