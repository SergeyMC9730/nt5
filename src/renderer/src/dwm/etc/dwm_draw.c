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

#include <string.h>

// draw dwm context
void _ntDwmDrawContext(struct dwm_context *ctx) {
    if (ctx->theme.basic.background_color.a != 0x00) ClearBackground(ctx->theme.basic.background_color);

    rsb_array_Int *pids = _ntDwmGetProcesses(ctx);

    renderer_state_t *st = _ntRendererGetState();

    for (size_t i = 0; i < pids->len; i++) {
        // struct dwm_window *ptr = ctx->windows->objects + i;
        int pid = RSBGetAtIndexInt(pids, i);

        struct dwm_window *ptr = _ntDwmGetProcess(ctx, pid);

        if (ptr != NULL) {
            _ntUpdateWindow(ptr, ctx);

            if (!ptr->hidden.state) {
                _ntDrawWindow(ptr, ctx);
            }
        }
    }
    
    RSBDestroyInt(pids);

    // window movement check

    Vector2 mouse = GetMousePosition();

    if (ctx->selected_window != NULL) {
        ctx->selected_window->post_moving.state = false;

        ctx->selected_window->titlebar_rect.x -= (24 * st->scaling);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if ( CheckCollisionPointRec(mouse, ctx->selected_window->titlebar_rect)) {
                if (ctx->selected_window->moving.ability) {
                    Vector2 mouse_delta = GetMouseDelta();

                    ctx->selected_window->moving.state = true;
                    ctx->selected_window->post_moving.state = false;

                    ctx->selected_window->position.x += mouse_delta.x;
                    ctx->selected_window->position.y += mouse_delta.y;
                }
            } else if (ctx->selected_window->moving.state) {
                Vector2 mouse_delta = GetMouseDelta();

                // ctx->selected_window->moving.state = true;
                ctx->selected_window->post_moving.state = true;

                ctx->selected_window->position.x += mouse_delta.x;
                ctx->selected_window->position.y += mouse_delta.y;
            }
        } else {
            ctx->selected_window->moving.state = false;
        }

        ctx->selected_window->titlebar_rect.x += (24 * st->scaling);
    }    
}