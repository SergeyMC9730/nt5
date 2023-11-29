#include <nt5emul/renderer.h>

#include <unistd.h>

#include <pthread.h>

// expose internal state
extern renderer_state_t _renderer_state;

void _renderer_create_environment() {
	if (_renderer_state.thread != 0) {
		_renderer_close_environment();
	}

	pthread_create(&_renderer_state.thread, NULL, _renderer_thread, NULL);

		// wait for renderer to be ready
	while (!(_renderer_state.status & RENDERER_READY)) {
		// wait 0.33 seconds before checking again
		usleep(1000000 / 3);
	}
}