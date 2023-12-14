#include <nt5emul/dwm/window.h>
#include <nt5emul/dwm/context.h>

void _ntCloseWindow(struct dwm_window *wnd, void *ctx_ptr) {
    if (!wnd->closed.ability) return;

    struct dwm_context *ctx = (struct dwm_context *)ctx_ptr;

    wnd->closed.state = true;
    
    if (ctx->selected_window == wnd) {
        ctx->selected_window = NULL;
    }
}