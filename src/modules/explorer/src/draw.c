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

void explorer_draw(struct dwm_window *wnd, void *user) {
    // struct dwm_context *ctx = _ntDwmGetGlobal();
    // struct local_module_state *lst = (struct local_module_state *)user;

    // // printf("Explorer draw! (%d)\n", lst->fs->base.items_total);

    // Vector2 sz;
    // sz.x = wnd->framebuffer.texture.width;
    // sz.y = wnd->framebuffer.texture.height;

    // // printf("y: %d\n", wnd->framebuffer.texture.height / 2);

    // float offset = ((float)GetRenderHeight() * 181.f) / 420.f;

    // Vector2 scr_pos;
    // scr_pos.x = (int)wnd->content_position.x;
    // scr_pos.y  = GetRenderHeight() - wnd->position.y + offset;

    // if (wnd->moving.state || wnd->post_moving.state) {
    //     Vector2 delta = GetMouseDelta();
        
    //     scr_pos.x += delta.x;
    //     scr_pos.y += delta.y;
    // }

    // _ntRendererDrawScreenPortion((Vector2){}, scr_pos, sz);

    // Color col = BLACK;
    // col.a = 220;

    // DrawRectangle(0, 0, sz.x, sz.y, col);

    // Vector2 m = _ntDwmGetLocalMousePosition(ctx);

    // DrawRectangle(m.x, m.y, 8, 8, RED);

    // _ntTuiDrawMenu(lst->fs->base);

    _ntRendererRunLuaScript("test.lua");
}