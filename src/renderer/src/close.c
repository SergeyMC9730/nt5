#include <nt5emul/renderer.h>

#include <raylib.h>

void _ntRendererCloseEnvironment() {
	renderer_state_t *st = _ntRendererGetState();

	st->status |= RENDERER_REQUESTED_STOP;

	_ntRendererJoin();

	st->status = 0;
}