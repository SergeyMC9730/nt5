#include <stdio.h>

#include <nt5emul/boot.h>
#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <nt5emul/dwm/context.h>

#include <cJSON.h>

#include <raylib.h>

#include <sys/stat.h>

void _boot_begin() {
	// create "nt" folder
	mkdir("nt", 0777);

	// init NT renderer
	_ntRendererCreateEnvironment();
	
	// begin installation process if config is not found
	if (!FileExists("nt/config.json")) {
		_boot_install_begin();

		return;
	}

	// _boot_try_parse_explorer();
	struct dwm_context *ctx = _ntCreateDwmContext("ntresources/basic.theme");

	struct dwm_window wnd = _ntCreateWindow("TEST", (Vector2){100, 100});

	wnd.position = (Vector2){200, 200};

	_ntPushWindow(ctx, wnd);

	renderer_state_t * st = _ntRendererGetState();

	st->layers[0].user = ctx;
	st->layers[0].draw = _ntDrawDwmContext;

	// _ntDestroyDwmContext(ctx);
}
