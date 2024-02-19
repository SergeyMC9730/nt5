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
#include <nt5emul/sort.h>

#include <stdio.h>

rsb_array_Int *_ntGetDWMProcesses(struct dwm_context *ctx) {
    rsb_array_Int *a = RSBCreateArrayInt();
    
    int i = 0;
    int l = ctx->windows->len;

    int current_pid = -1;

    // loop through all processes
    while (i < l) {
        struct dwm_window wnd = RSBGetAtIndexDWMWindow(ctx->windows, i);

        // printf("wnd info: i=%d; pid=%d =>", i, wnd.process.pid);

        if (wnd.closed.state) {
            i++;

            // printf(" ignored (closed)\n");

            continue;
        }

        // printf("process %d %d | ", current_pid, wnd.process.pid);

        // check if wnd is the selected one
        if (ctx->selected_window != NULL && ctx->selected_window->process.pid == wnd.process.pid) {
            i++;

            // printf(" ignored* (selected)\n");

            current_pid = wnd.process.pid;

            // dont add this pid to the array
            continue;
        }

        // printf(" added\n");

        // add pid to the array
        RSBAddElementInt(a, wnd.process.pid);
        
        i++;
    }

    // sort array from the lowest pid to the highest one
    qsort(a->objects, a->len, sizeof(int), _ntSortComparison);

    if (current_pid != -1) RSBAddElementInt(a, current_pid);
    
    // RSBPrintArrayInt(a); printf("\n");

    return a;
}