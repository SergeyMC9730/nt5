#include <nt5emul/renderer.h>

// expose internal state
extern renderer_state_t _renderer_state;

void _renderer_update() {
	for (unsigned short i = 0; i < RENDERER_LAYERS; i++) {
		// update each layer

		if (_renderer_state.layers[i].update != NULL)_renderer_state.layers[i].update();
	}
}