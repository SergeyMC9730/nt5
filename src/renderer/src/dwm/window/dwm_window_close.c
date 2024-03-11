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

#include <nt5emul/dwm/window.h>
#include <nt5emul/dwm/context.h>

void _ntCloseWindow(struct dwm_window *wnd, void *ctx_ptr) {
    if (!wnd->closed.ability) return;

    struct dwm_context *ctx = (struct dwm_context *)ctx_ptr;

    rsb_array_Int *list = _ntDwmGetProcessesRaw(ctx);

    int idx = -1;
    for (int i = 0; i < list->len; i++) {
        int pid = RSBGetAtIndexInt(list, i);
        if (pid == wnd->process.pid) {
            idx = i;
            break;
        }
    }

    RSBDestroyInt(list);

    if (wnd->on_close) {
        wnd->on_close(wnd, wnd->ctx);
    }

    // wnd->closed.state = true;

    UnloadRenderTexture(wnd->framebuffer);
    
    if (ctx->selected_window == wnd) {
        ctx->selected_window = NULL;
    }

    printf("idx=%d\n", idx);

    // to prevent heap-use-after-free bug we will get pid of the currently rendering window
    int rendered_pid = -1;
    
    if (ctx->rendered_window != NULL) {
        rendered_pid = ctx->rendered_window->process.pid;
    }

    if (idx != -1) {
        RSBPopElementAtIndexDWMWindow(ctx->windows, idx);
    }

    if (rendered_pid != -1) {
        // now we would get address of the currently rendering window inside the new window array
        ctx->rendered_window = _ntDwmGetProcess(ctx, rendered_pid);
    }
}