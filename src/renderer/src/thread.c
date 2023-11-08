#include <nt5emul/renderer.h>

#include <raylib.h>

#include <string.h>

void _renderer_update() {
	for (unsigned short i = 0; i < 64; i++) {
		if (_renderer_state.layers[i].update != NULL)_renderer_state.layers[i].update();
	}
}

void _renderer_draw() {
	for (unsigned short i = 0; i < 64; i++) {
		if (_renderer_state.layers[i].draw != NULL)_renderer_state.layers[i].draw();
	}
}

void *_renderer_create_environment1(void *ptr) {
	InitWindow(640, 480, "NT5");

	if (_renderer_state.layers != NULL) {
		MemFree((void *)_renderer_state.layers);
	}

	int layers_size = sizeof(renderer_layer_t) * 64;

	_renderer_state.layers = (renderer_layer_t *)(MemAlloc(layers_size));

	memset(_renderer_state.layers, 0, layers_size);

	SetTargetFPS(60);

	_renderer_state.status = RENDERER_READY;
	
	while (!WindowShouldClose()) {
		if (_renderer_state.status & RENDERER_REQUESTED_STOP) break;

		_renderer_update();

		BeginDrawing();

		ClearBackground(BLACK);
	
		_renderer_draw();

		EndDrawing();
	}

	CloseWindow();

	return NULL;
} 

void _renderer_create_environment() {
	if (_renderer_state.thread != 0) {
		_renderer_close_environment();
	}

	pthread_create(&_renderer_state.thread, NULL, _renderer_create_environment1, NULL);

	while (!(_renderer_state.status & RENDERER_READY)) {
		usleep(1000000 / 3);
	}
}