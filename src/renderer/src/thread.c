#include <nt5emul/renderer.h>

#include <raylib.h>

#include <string.h>

// expose internal state
extern renderer_state_t _renderer_state;

void *_renderer_thread(void *ptr) {
	// init raylib window
	InitWindow(640, 480, "NT5");

	// check if layers already exists and free if they
	if (_renderer_state.layers != NULL) {
		MemFree((void *)_renderer_state.layers);
	}

	// calculate layer array size
	int layers_size = sizeof(renderer_layer_t) * RENDERER_LAYERS;

	// allocate array
	_renderer_state.layers = (renderer_layer_t *)(MemAlloc(layers_size));

	// make it empty
	memset(_renderer_state.layers, 0, layers_size);

	// set window fps to main monitor's refresh rate
	SetTargetFPS(GetMonitorRefreshRate(0));

	// set status as READY
	_renderer_state.status = RENDERER_READY;
	
	while (!WindowShouldClose()) {
		if (_renderer_state.status & RENDERER_REQUESTED_STOP) break;

		// update renderer
		_renderer_update();

		// begin drawing
		BeginDrawing();

		// draw everything
		_renderer_draw();

		// complete drawing
		EndDrawing();
	}

	CloseWindow();

	return NULL;
}