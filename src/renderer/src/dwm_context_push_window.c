#include <nt5emul/dwm/context.h>

#include <string.h>

// push window to the dwm context
void _ntPushWindow(struct dwm_context *ctx, struct dwm_window wnd) {
    RSBAddElementDWMWindow(ctx->windows, wnd);
}