#include <nt5emul/dwm/context.h>

// get process by process id
struct dwm_window *_ntGetDWMProcess(struct dwm_context *ctx, int pid) {
    int l = ctx->windows->len;
    int i = 0;

    while (i < l) {
        struct dwm_window *ptr = ctx->windows->objects + i;

        if (ptr->process.pid == pid) return ptr;

        i++;
    }

    return NULL;
}