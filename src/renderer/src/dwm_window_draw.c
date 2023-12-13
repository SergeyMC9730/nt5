#include <nt5emul/dwm/window.h>
#include <nt5emul/dwm/context.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void _ntDrawWindow(struct dwm_window *wnd, void *ctx_ptr) {
    struct dwm_context *ctx = (struct dwm_context *)ctx_ptr;

    Rectangle sz = {
        wnd->position.x, wnd->position.y,
        wnd->size.x, wnd->size.y
    };

    Color border1 = ctx->theme.basic.active_border_color;
    Color border2 = ctx->theme.basic.window_base_color;

    Color border3 = ctx->theme.basic.button_dk_shadow;
    Color border4 = ctx->theme.basic.button_shadow_color;

    Color *gr = ctx->theme.basic.window_inactive_title_gradient;

    size_t title_bar_size = ctx->theme.basic.title_bar_size;

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

    DrawRectangle(sz.x + 1, sz.y + 2, sz.width - 3, sz.height - 3, border1);

    DrawRectangleGradientH(wnd->titlebar_rect.x, wnd->titlebar_rect.y, wnd->titlebar_rect.width, wnd->titlebar_rect.height, gr[0], gr[1]);

    float font_sz = ctx->fonts.tahoma8_bld.real_size * 0.5f;
    float spacing = 1.f;

    Vector2 text_sz = MeasureTextEx(ctx->fonts.tahoma8_bld.font, wnd->title, font_sz, spacing);

    int y_align = (title_bar_size - text_sz.y) / 2;

    DrawTextEx(ctx->fonts.tahoma8_bld.font, wnd->title, (Vector2){
        wnd->titlebar_rect.x + 2, wnd->titlebar_rect.y + y_align
    }, font_sz, spacing, ctx->theme.basic.active_title_text_color);

    if (wnd->draw != NULL) wnd->draw(wnd, ctx);
}