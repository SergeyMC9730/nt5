#include <nt5emul/modules/logo/state.h>

#ifndef NULL
#define NULL (void *)0
#endif

void logo_update(void *user) {
    if (_state.old_update != NULL) _state.old_update(_state.old_ctx);

    if (!_state.init_complete) {
        _state.logo_texture = LoadTexture("nt/images/user/ui/mslogo.jpg");
        _state.init_complete = true;
    }

    int frames_per_step = GetFPS() / 60;
    int col_step = 1;
    if (frames_per_step == 0) {
        frames_per_step = 1;
        col_step = 60 / GetFPS();
    }

    int max_val = 0xFF + 1 - col_step;

    if (
        (_state.transition_color.a != max_val && _state.transition_color.a != 0xFF) && 
        !(_state.frames % frames_per_step)
    ) {
        _state.transition_color.a += col_step;
    }

    if (_state.transition_color.a == max_val) {
        _state.transition_color.a = 0xFF;
    }

    _state.frames++;
}