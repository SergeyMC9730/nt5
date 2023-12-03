#include <nt5emul/renderer.h>

// expose internal state
extern renderer_state_t _renderer_state;

renderer_state_t *_ntRendererGetState() {
    return &_renderer_state;
}