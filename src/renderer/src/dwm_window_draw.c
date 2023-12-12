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

    Vector2 lighter_border_size[3] = {
        {
            wnd->position.x,
            wnd->position.y + wnd->size.y - 1,
        },
        {
            wnd->position.x,
            wnd->position.y
        },
        {
            wnd->position.x + wnd->size.x - 1,
            wnd->position.y,
        }
    };

    Vector2 lighter_border_size2[3] = {
        {
            wnd->position.x + 1,
            wnd->position.y + wnd->size.y - 2,
        },
        {
            wnd->position.x + 1,
            wnd->position.y - 1,
        },
        {
            wnd->position.x + wnd->size.x - 1 - 1,
            wnd->position.y - 1,
        }
    };

    Color border1 = ctx->theme.basic.inactive_border_color;

    if (ctx->selected_window == wnd) {
        border1 = ctx->theme.basic.active_border_color;
    }

    DrawLineStrip(lighter_border_size, 3, border1);

    if (wnd->draw != NULL) wnd->draw(wnd, ctx);
}