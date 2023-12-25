#include <nt5emul/modules/logo/state.h>
#include <nt5emul/renderer.h>

void logo_reset() {
    renderer_state_t *st = _ntRendererGetState();

    st->layers[RENDERER_LAYERS - 1].draw = _state.old_draw;
    st->layers[RENDERER_LAYERS - 1].update = _state.old_update;
}