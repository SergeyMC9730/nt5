#include <nt5emul/renderer.h>

void _renderer_join() {
    pthread_join(_renderer_state.thread, NULL);
}