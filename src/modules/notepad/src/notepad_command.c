
#include <nt5emul/modules/notepad/state.h>
#include <nt5emul/modules/notepad/notepad_command.h>
#include <nt5emul/dwm/context.h>
#include <nt5emul/dwm/window.h>


bool notepad_command(void *data) {
    
    
struct dwm_window wnd = _ntCreateWindow("notepad", (Vector2){500, 150});

    wnd.draw = notepad_draw;
    wnd.update = notepad_update;

    wnd.filled.state = true;
    wnd.filled.ability = true;

    wnd.position = (Vector2){50, 50};
    
    _ntPushWindow(_ntDwmGetGlobal(), wnd);


    return true;
}

void notepad_draw(void *ctx) {
    
}

void notepad_update(void *ctx) {
    
}
