#include <nt5emul/dwm/context.h>

#include <string.h>

// push window to the dwm context
void _ntPushWindow(struct dwm_context *ctx, struct dwm_window wnd) {
    struct dwm_window wnd2 = wnd;

    wnd2.process.pid = ++ctx->global_process_increment;
    wnd2.moving.ability = true;

    RSBAddElementDWMWindow(ctx->windows, wnd2);

    struct dwm_window *wnd_ptr = ctx->windows->objects + (ctx->windows->current_index - 1);

    ctx->selected_window = wnd_ptr;

    printf("window %d with pos %f:%f; size %f:%f\n",wnd2.process.pid, wnd2.position.x, wnd2.position.y, wnd2.size.x, wnd2.size.y);
}