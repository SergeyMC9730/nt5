#include <nt5emul/renderer.h>

void _ntRendererJoin() {
    renderer_state_t *st = _ntRendererGetState();

    pthread_join(st->thread, NULL);
}