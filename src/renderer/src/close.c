#include <nt5emul/renderer.h>

#include <raylib.h>

void _renderer_close_environment() {
	_renderer_state.status |= RENDERER_REQUESTED_STOP;

	_renderer_join();

	_renderer_state.status = 0;
}