#include <nt5emul/dwm/context.h>
#include <nt5emul/sort.h>

#include <stdio.h>

rsb_array_Int *_ntGetDWMProcesses(struct dwm_context *ctx) {
    rsb_array_Int *a = RSBCreateArrayInt();
    
    int i = 0;
    int l = ctx->windows->len;

    int current_pid = -1;

    // loop through all processes
    while (i < l) {
        struct dwm_window wnd = RSBGetAtIndexDWMWindow(ctx->windows, i);

        if (wnd.closed.state) {
            i++;

            continue;
        }

        // printf("process %d %d | ", current_pid, wnd.process.pid);

        // check if wnd is the selected one
        if (ctx->selected_window != NULL && ctx->selected_window->process.pid == wnd.process.pid) {
            i++;

            current_pid = wnd.process.pid;

            // dont add this pid to the array
            continue;
        }

        // add pid to the array
        RSBAddElementInt(a, wnd.process.pid);
        
        i++;
    }

    // sort array from the lowest pid to the highest one
    qsort(a->objects, a->len, sizeof(int), _ntSortComparison);

    if (current_pid != -1) RSBAddElementInt(a, current_pid);
    
    RSBPrintArrayInt(a); printf("\n");

    return a;
}