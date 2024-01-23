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

#include <nt5emul/dwm/window.h>
#include <nt5emul/dwm/context.h>
#include <nt5emul/dwm/button.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <nt5emul/renderer.h>

void _ntDrawWindow(struct dwm_window *wnd, void *ctx_ptr) {
    struct dwm_context *ctx = (struct dwm_context *)ctx_ptr;

    renderer_state_t *st = _ntRendererGetState();

    Rectangle sz = {
        wnd->position.x, wnd->position.y,
        wnd->size.x * st->scaling, wnd->size.y * st->scaling
    };

    Color border1 = ctx->theme.basic.active_border_color;
    Color border2 = ctx->theme.basic.window_base_color;

    Color border3 = ctx->theme.basic.button_dk_shadow;
    Color border4 = ctx->theme.basic.button_shadow_color;

    Color *gr = ctx->theme.basic.window_inactive_title_gradient;

    float title_bar_size = ctx->theme.basic.title_bar_size;

    if (wnd->draw) {
        BeginTextureMode(wnd->framebuffer);
            wnd->draw(wnd, wnd->ctx);
        EndTextureMode();
    }

    DrawRectangle(sz.x + (1 * st->scaling), sz.y + (2 * st->scaling), sz.width - (3 * st->scaling), sz.height - (3 * st->scaling), border1);

    _ntRendererDrawSizedTexture(wnd->framebuffer.texture, (Vector2){1.f, -1.f}, (Vector2){
        wnd->titlebar_rect.x - (3 * st->scaling), wnd->titlebar_rect.y + wnd->titlebar_rect.height
    }, (Vector2){});

    if (ctx->selected_window == wnd) {
        gr = ctx->theme.basic.window_active_title_gradient;
    }

    DrawLine(sz.x, sz.y, sz.x + sz.width - 1, sz.y, border1);
    DrawLine(sz.x, sz.y, sz.x, sz.y + sz.height, border1);

    DrawLine(sz.x - 1, sz.y + sz.height, sz.x + sz.width, sz.y + sz.height, border3);
    DrawLine(sz.x + sz.width, sz.y + sz.height, sz.x + sz.width, sz.y, border3);

    DrawLine(sz.x + 1, sz.y + 1, sz.x + sz.width - 2, sz.y + 1, border2);
    DrawLine(sz.x + 1, sz.y + 1, sz.x + 1, sz.y + sz.height - 1, border2);

    DrawLine(sz.x - 1 + 1, sz.y + sz.height - 1, sz.x + sz.width - 1, sz.y + sz.height - 1, border4);
    DrawLine(sz.x + sz.width - 1, sz.y + sz.height - 1, sz.x + sz.width - 1, sz.y + 1, border4);



    DrawRectangleGradientH(wnd->titlebar_rect.x, wnd->titlebar_rect.y, wnd->titlebar_rect.width, wnd->titlebar_rect.height, gr[0], gr[1]);

    float font_sz = ctx->fonts.tahoma8_bld.real_size;
    float spacing = ctx->fonts.tahoma8_bld.spacing;

    Vector2 text_sz = MeasureTextEx(ctx->fonts.tahoma8_bld.font, wnd->title, font_sz, spacing);

    int y_align = (title_bar_size - text_sz.y) / 2;

    DrawTextEx(ctx->fonts.tahoma8_bld.font, wnd->title, (Vector2){
        wnd->titlebar_rect.x + (2 * st->scaling), wnd->titlebar_rect.y + y_align
    }, font_sz, spacing, ctx->theme.basic.active_title_text_color);


    struct dwm_button btn_test = {};

    btn_test.text = "X";

    btn_test.button.width = 16 * st->scaling;
    btn_test.button.height = 14 * st->scaling;

    btn_test.activated.ability = true;
    btn_test.howered.ability = true;

    int y_align2 = (title_bar_size - btn_test.button.height) / 2;

    btn_test.button.x = sz.x + sz.width - btn_test.button.width - (6 * st->scaling);
    btn_test.button.y = sz.y + y_align2 + (2 * st->scaling);

    // printf("button result: %d\n", _ntDrawDWMButton(ctx, btn_test));
    if (_ntDrawDWMButton(ctx, &btn_test) && wnd == ctx->selected_window) {
        printf("closing window\n");
        _ntCloseWindow(wnd, ctx);
    }

    wnd->moving.ability = !(btn_test.howered.state);
}