#include <nt5emul/dwm/context.h>

#include <string.h>

// draw dwm context
void _ntDrawDwmContext(struct dwm_context *ctx) {
    ClearBackground(ctx->theme.basic.background_color);

    for (size_t i = 0; i < ctx->windows->len; i++) {
        struct dwm_window *ptr = ctx->windows->objects + i;
    
        _ntDrawWindow(ptr, ctx);
    }
}