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
#include <nt5emul/renderer.h>
#include <nt5emul/timer.h>

#include <string.h>

#include <stdio.h>

struct nt_push_window_args {
    struct dwm_context *ctx;
    struct dwm_window wnd;
};

// create window framebuffer  in main 
// thread in case if we are trying to 
// create window outside the renderer 
// thread
void _ntPushWindowFb(void *ctx) {
    struct nt_push_window_args *args = (struct nt_push_window_args *)ctx;

    renderer_state_t *st = _ntRendererGetState();

    args->wnd.framebuffer = LoadRenderTexture(
        (args->wnd.size.x * st->scaling) - (2 * st->scaling), 
        (args->wnd.size.y * st->scaling) - 
            args->wnd.titlebar_rect.height - (4 * st->scaling)
    );
}

// push window to the dwm context
int _ntDwmPushWindow(struct dwm_context *ctx, struct dwm_window wnd) {
    struct dwm_window wnd2 = wnd;

    // set process id
    wnd2.process.pid = ++ctx->global_process_increment;
    wnd2.moving.ability = true;

    _ntUpdateWindow(&wnd2, ctx);

    if (!_ntRendererInThread()) {
        wnd2.framebuffer.texture.width = 0;

        // create argument list
        struct nt_push_window_args *args = (struct nt_push_window_args *)malloc(sizeof(struct nt_push_window_args));
        args->ctx = ctx;
        args->wnd = wnd2;
        
        // all gl fuctions should be runned inside the renderer thread
        _ntRendererPushQueue(_ntPushWindowFb, args);

        while (args->wnd.framebuffer.texture.width == 0) {
            _ntSetupTimerSync(0.01);
        }

        wnd2 = args->wnd;

        free(args);
    } else {
        renderer_state_t *st = _ntRendererGetState();
        wnd2.framebuffer = LoadRenderTexture((wnd2.size.x * st->scaling) - (2 * st->scaling), (wnd2.size.y * st->scaling) - wnd2.titlebar_rect.height - (4 * st->scaling ));
    }

    // to prevent heap-use-after-free bug we will get pid of the currently rendering window
    int rendered_pid = -1;
    
    if (ctx->rendered_window != NULL) {
        rendered_pid = ctx->rendered_window->process.pid;
    }

    // add window to the window array
    RSBAddElementDWMWindow(ctx->windows, wnd2);
    struct dwm_window *wnd_ptr = ctx->windows->objects + (ctx->windows->current_index - 1);

    // make it selected
    ctx->selected_window = wnd_ptr;

    if (rendered_pid != -1) {
        // now we would get address of the currently rendering window inside the new window array
        ctx->rendered_window = _ntDwmGetProcess(ctx, rendered_pid);
    }

    printf("window %d with pos %f:%f; size %f:%f\n",wnd2.process.pid, wnd2.position.x, wnd2.position.y, wnd2.size.x, wnd2.size.y);

    for (int i = 0; i < ctx->window_create_event->len; i++) {
        renderer_event_t ev = RSBGetAtIndexEvent(ctx->window_create_event, i);

        if (ev.callback != NULL) ev.callback(wnd_ptr);
    }

    return wnd_ptr->process.pid;
}