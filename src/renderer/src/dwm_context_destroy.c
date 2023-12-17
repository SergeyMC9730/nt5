#include <nt5emul/dwm/context.h>

#include <string.h>

// destroy dwm context
void _ntDestroyDwmContext(struct dwm_context *ctx) {
    // free theme path string
    free((char *)ctx->theme.basic.theme_path);

    // destroy windows
    RSBDestroyDWMWindow(ctx->windows);

    // unload fonts

    UnloadFont(ctx->fonts.tahoma8_std.font);
    UnloadFont(ctx->fonts.tahoma8_bld.font);

    // free context
    free(ctx);
}