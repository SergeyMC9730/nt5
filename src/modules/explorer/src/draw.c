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

#include <nt5emul/modules/explorer/state.h>
#include <nt5emul/dwm/context.h>
#include <nt5emul/renderer.h>
#include <nt5emul/dwm/window.h>
#include <nt5emul/tui/text.h>

#ifndef NULL
#define NULL (void *)0
#endif

#include <stdio.h>

void explorer_draw_bg(struct dwm_window *wnd) {
    Vector2 sz;
    sz.x = wnd->framebuffer.texture.width;
    sz.y = wnd->framebuffer.texture.height;

    Vector2 scr_pos;
    scr_pos.x = -(int)wnd->content_position.x;
    scr_pos.y = -(int)wnd->content_position.y;

    if (wnd->moving.state || wnd->post_moving.state) {
        Vector2 delta = GetMouseDelta();
        
        scr_pos.x -= delta.x;
        scr_pos.y -= delta.y;
    }

    renderer_state_t *st = _ntRendererGetState();

    _ntRendererDrawSizedTexture(st->framebuffer.texture, (Vector2){1.f, -1.f}, scr_pos, (Vector2){}, true);
}

void explorer_draw(struct dwm_window *wnd, void *user) {
    struct dwm_context *ctx = _ntDwmGetGlobal();
    struct local_module_state *lst = (struct local_module_state *)user;
    Vector2 m = _ntDwmGetLocalMousePosition(ctx);
    renderer_state_t *st = _ntRendererGetState();
    Color col = BLACK;
    col.a = 220;

    Vector2 sz;
    sz.x = wnd->framebuffer.texture.width;
    sz.y = wnd->framebuffer.texture.height;

    ClearBackground(BLACK);

    _ntRendererApplyBlurEffect((renderer_event_t){explorer_draw_bg, wnd});

    // DrawRectangle(0, 0, sz.x, sz.y, col);
    DrawRectangle(m.x, m.y, 8, 8, RED);
    _ntTuiDrawMenu(lst->fs->base);
}