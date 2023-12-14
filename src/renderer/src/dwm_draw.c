#include <nt5emul/dwm/context.h>

#include <string.h>

// draw dwm context
void _ntDrawDwmContext(struct dwm_context *ctx) {
    ClearBackground(ctx->theme.basic.background_color);

    rsb_array_Int *pids = _ntGetDWMProcesses(ctx);

    for (size_t i = 0; i < pids->len; i++) {
        // struct dwm_window *ptr = ctx->windows->objects + i;
        int pid = RSBGetAtIndexInt(pids, i);

        struct dwm_window *ptr = _ntGetDWMProcess(ctx, pid);

        if (ptr != NULL && !ptr->hidden.state) {
            _ntUpdateWindow(ptr, ctx);
            _ntDrawWindow(ptr, ctx);
        }
    }
    
    RSBDestroyInt(pids);

    // window movement check

    Vector2 mouse = GetMousePosition();

    if (ctx->selected_window != NULL) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if ( CheckCollisionPointRec(mouse, ctx->selected_window->titlebar_rect)) {
                if (ctx->selected_window->moving.ability) {
                    Vector2 mouse_delta = GetMouseDelta();

                    ctx->selected_window->moving.state = true;

                    ctx->selected_window->position.x += mouse_delta.x;
                    ctx->selected_window->position.y += mouse_delta.y;
                }
            } else if (ctx->selected_window->moving.state) {
                Vector2 mouse_delta = GetMouseDelta();

                // ctx->selected_window->moving.state = true;

                ctx->selected_window->position.x += mouse_delta.x;
                ctx->selected_window->position.y += mouse_delta.y;
            }
        } else {
            ctx->selected_window->moving.state = false;
        }
    }
}