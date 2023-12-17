#include <nt5emul/dwm/window.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct dwm_window _ntCreateWindow(const char *title, Vector2 size) {
    struct dwm_window wnd = {0};

    // set window parameters
    wnd.closed.ability = true;
    wnd.filled.ability = true;
    wnd.hidden.ability = true;
    wnd.moving.ability = true;

    wnd.closed.state = false;
    wnd.hidden.state = false;
    wnd.filled.state = false;
    wnd.moving.state = true;

    // set size
    wnd.size = size;
    // set title
    wnd.title = title;

    return wnd;
}