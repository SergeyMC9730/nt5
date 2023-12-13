#include <nt5emul/dwm/window.h>
#include <nt5emul/dwm/context.h>

#include <stdio.h>

void _ntUpdateWindow(struct dwm_window *wnd, void *context) {
    Vector2 mouse = GetMousePosition();

    // printf("%f %f\n", mouse.x, mouse.y);

    struct dwm_context *ctx = (struct dwm_context *)context;

    size_t title_bar_size = ctx->theme.basic.title_bar_size;

    Rectangle sz = {
        wnd->position.x, wnd->position.y,
        wnd->size.x, wnd->size.y
    };

    Rectangle title_bar_rect = {
        sz.x + 2, sz.y + 3,
        sz.width - 5, title_bar_size
    };

    wnd->titlebar_rect = title_bar_rect;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mouse, sz)) {
            ctx->selected_window = wnd;

            // rsb_array_Int *pids = _ntGetDWMProcesses(ctx);

	        // RSBDestroyInt(pids);
        }
    }    
}