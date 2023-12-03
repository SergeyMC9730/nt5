#include <nt5emul/renderer.h>

#include <unistd.h>

#include <pthread.h>

void _ntRendererCreateEnvironment() {
	renderer_state_t *st = _ntRendererGetState();

	if (st->thread != 0) {
		_ntRendererCloseEnvironment();
	}

	pthread_create(&st->thread, NULL, _ntRendererThread, NULL);

		// wait for renderer to be ready
	while (!(st->status & RENDERER_READY)) {
		// wait 0.33 seconds before checking again
		usleep(1000000 / 3);
	}
}