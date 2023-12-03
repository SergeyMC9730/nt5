#include <nt5emul/renderer.h>

#include <raylib.h>

#include <string.h>

void *_ntRendererThread(void *ptr) {
	// init raylib window
	InitWindow(640, 480, "NT5");

	renderer_state_t *st = _ntRendererGetState();

	// check if layers already exists and free if they
	if (st->layers != NULL) {
		MemFree(st->layers);
	}

	// calculate layer array size
	int layers_size = sizeof(renderer_layer_t) * RENDERER_LAYERS;

	// allocate array
	st->layers = (renderer_layer_t *)(MemAlloc(layers_size));

	// make it empty
	memset(st->layers, 0, layers_size);

	// set window fps to main monitor's refresh rate
	SetTargetFPS(GetMonitorRefreshRate(0));

	// set status to READY
	st->status = RENDERER_READY;
	
	while (!WindowShouldClose()) {
		if (st->status & RENDERER_REQUESTED_STOP) break;

		// update renderer
		_ntRendererUpdate();

		// begin drawing
		BeginDrawing();

		// draw everything
		_ntRendererDraw();

		// complete drawing
		EndDrawing();
	}

	CloseWindow();

	return NULL;
}