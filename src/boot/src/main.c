#include <stdio.h>

#include <nt5emul/boot.h>
#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <nt5emul/dwm/context.h>

#include <cJSON.h>

#include <raylib.h>

#include <sys/stat.h>

void _boot_begin_debug(void *user) {
	struct dwm_context *ctx = (struct dwm_context *)user;

	if (IsKeyPressed(KEY_F1)) {
		struct dwm_window wnd = _ntCreateWindow("Settings !", (Vector2){200, 300});

		wnd.position = (Vector2){50, 50};

		printf("creating window\n");

		_ntPushWindow(ctx, wnd);
	}
}


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

	SetWindowSize(1024, 768);
	// SetTargetFPS();

	// _boot_try_parse_explorer();
	struct dwm_context *ctx = _ntCreateDwmContext("ntresources/basic.theme");

	for (int i = 0; i < 1; i++) {
		int c = i * 50;

		struct dwm_window wnd = _ntCreateWindow("Settings !", (Vector2){200 + c, 300});

		wnd.position = (Vector2){50 + c, 50 + c};

		_ntPushWindow(ctx, wnd);
	}

	renderer_state_t * st = _ntRendererGetState();

	st->layers[0].user = ctx;
	st->layers[0].draw = _ntDrawDwmContext;

	st->layers[1].user = ctx;
	st->layers[1].update = _boot_begin_debug;

	// _ntDestroyDwmContext(ctx);
}
