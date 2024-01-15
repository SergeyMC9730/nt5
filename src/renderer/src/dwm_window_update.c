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
#include <nt5emul/renderer.h>

#include <stdio.h>

void _ntUpdateWindow(struct dwm_window *wnd, void *context) {
    Vector2 mouse = GetMousePosition();

    // printf("%f %f\n", mouse.x, mouse.y);

    struct dwm_context *ctx = (struct dwm_context *)context;

    renderer_state_t *st = _ntRendererGetState();

    float title_bar_size = ctx->theme.basic.title_bar_size;

    Rectangle sz = {
        wnd->position.x, wnd->position.y,
        wnd->size.x * st->scaling, wnd->size.y * st->scaling
    };

    Rectangle title_bar_rect = {
        sz.x + (2 * st->scaling), sz.y + (3 * st->scaling),
        sz.width - (5 * st->scaling), title_bar_size
    };

    wnd->titlebar_rect = title_bar_rect;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mouse, sz)) {
            ctx->selected_window = wnd;

            // rsb_array_Int *pids = _ntGetDWMProcesses(ctx);

	        // RSBDestroyInt(pids);
        }
    }    
}