/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  Sergei Baigerov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact Sergei Baigerov -- @dogotrigger in Discord
*/

#include <stdio.h>

#include <nt5emul/boot.h>
#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <nt5emul/dwm/context.h>

#include <cJSON.h>

#include <raylib.h>

#include <sys/stat.h>

#include <cterm/libcterm.h>
#include <cterm/applications/api.h>

#include <nt5emul/nt_config.h>

#define SKIP_LOGO 1

// extern void register_command(char *command, char *helpdesc, bool helpHide, bool (*callback)(void *args));
extern cterm_command_reference_t find_command(char *command);

void _boot_begin_debug(void *user) {
	struct dwm_context *ctx = (struct dwm_context *)user;

	// check if F1 key is pressed
	if (IsKeyPressed(KEY_F1)) {
		// create window "Settings !"
		struct dwm_window wnd = _ntCreateWindow("Settings !", (Vector2){200, 300});

		// set position
		wnd.position = (Vector2){50, 50};

		// push window
		_ntPushWindow(ctx, wnd);
	}
}


void _boot_begin() {
	// create "nt" folder
	mkdir("nt", 0777);

	// init NT renderer
	_ntRendererCreateEnvironment();
	
	const char *config_path = "nt/config.json";

	struct nt_config config = _ntGetConfig(config_path);

	printf("config values: setup: %d; oobe; %d\n", config.setup_completed, config.oobe_completed);

	if (!config.setup_completed) {
		_boot_install_begin();

		return;
	}

	SetWindowSize(1024, 768);
	// SetTargetFPS(15);

	// _boot_try_parse_explorer();
	struct dwm_context *ctx = _ntCreateDwmContext("ntresources/basic.theme");

	// for (int i = 0; i < 1; i++) {
	// 	int c = i * 50;

	// 	struct dwm_window wnd = _ntCreateWindow("Settings !", (Vector2){200 + c, 300});

	// 	wnd.position = (Vector2){50 + c, 50 + c};

	// 	_ntPushWindow(ctx, wnd);
	// }

	renderer_state_t * st = _ntRendererGetState();

	st->layers[1].user = ctx;
	st->layers[1].update = _boot_begin_debug;

	_cterm_init();
	
	#if SKIP_LOGO == 0
	usleep(1000000);
	#else
	usleep(10000);
	#endif

	// load bootscreen
	cterm_command_reference_t ref = find_command("logo");

	// check if bootscreen module exist
	if (ref.callback) {
		// run it
		#if SKIP_LOGO == 0
		ref.callback(NULL);
		#endif

		// setup dwm layer in background
		st->layers[0].user = ctx;
		st->layers[0].draw = _ntDrawDwmContext;
	}

	#if SKIP_LOGO == 0
	// wait 5.5 seconds
	usleep(5500000);
	#endif

	// set background opacity to be fully transparent
	ctx->theme.basic.background_color.a = 0x00;

	// move dwm layer to 2 so we will be able to create and manipulate windows inside oobe
	st->layers[2].user = ctx;
	st->layers[2].draw = st->layers[0].draw;

	st->layers[0].draw = NULL;
	
	// load msoobe
	ref = find_command("msoobe");
	if (ref.callback) {
		// run it
		ref.callback(ctx);
	}
}
