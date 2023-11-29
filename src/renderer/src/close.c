#include <nt5emul/renderer.h>

#include <raylib.h>

// expose NT renderer
extern renderer_state_t _renderer_state;

void _renderer_close_environment() {
	_renderer_state.status |= RENDERER_REQUESTED_STOP;

	_renderer_join();

	_renderer_state.status = 0;
}