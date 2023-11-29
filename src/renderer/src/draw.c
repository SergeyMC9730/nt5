#include <nt5emul/renderer.h>

// expose internal state
extern renderer_state_t _renderer_state;

void _renderer_draw() {
	for (unsigned short i = 0; i < RENDERER_LAYERS; i++) {
		// draw each layer

		if (_renderer_state.layers[i].draw != NULL)_renderer_state.layers[i].draw();
	}
}