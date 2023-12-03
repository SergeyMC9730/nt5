#include <nt5emul/renderer.h>

void _ntRendererUpdate() {
	renderer_state_t *st = _ntRendererGetState();

	for (unsigned short i = 0; i < RENDERER_LAYERS; i++) {
		// update each layer

		if (st->layers[i].update != NULL) st->layers[i].update();
	}
}