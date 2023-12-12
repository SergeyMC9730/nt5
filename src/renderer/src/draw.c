#include <nt5emul/renderer.h>

void _ntRendererDraw() {
	renderer_state_t *st = _ntRendererGetState();

	for (unsigned short i = 0; i < RENDERER_LAYERS; i++) {
		// draw each layer

		if (st->layers[i].draw != NULL) st->layers[i].draw(st->layers[i].user);
	}
}