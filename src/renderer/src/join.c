#include <nt5emul/renderer.h>

// expose internal state
extern renderer_state_t _renderer_state;

void _renderer_join() {
    pthread_join(_renderer_state.thread, NULL);
}