#include <nt5emul/modules/logo/state.h>
#include <nt5emul/renderer.h>
#include <nt5emul/timer.h>
#include <nt5emul/modules/logo/logo_layer.h>

bool logo_command(void *data) {
    renderer_state_t *st = _ntRendererGetState();

    _state.old_draw = st->layers[RENDERER_LAYERS - 1].draw;
    _state.old_update = st->layers[RENDERER_LAYERS - 1].update;

    st->layers[RENDERER_LAYERS - 1].draw = logo_draw;
    st->layers[RENDERER_LAYERS - 1].update = logo_update;

    _state.transition_color = WHITE;
    _state.transition_color.a = 0;

    _ntInstallTimer(logo_reset, 5.f);

    return true;
}