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

#include <nt5emul/arrays/rsb_array_char.h>

#include <nt5emul/tui/environment.h>

#define SKIP_LOGO 0

// extern void register_command(char *command, char *helpdesc, bool helpHide, bool (*callback)(void *args));
extern cterm_command_reference_t find_command(char *command);

rsb_array_String *str_test;
char *str_test2;

bool _boot_run_command(const char *command, void *userdata) {
	// printf("running command %s\n", command);
	// load bootscreen
	cterm_command_reference_t ref = find_command((char *)command);

	// check if bootscreen module exist
	if (ref.callback) {
		// run it
		ref.callback(userdata);

		return true;
	}

	return false;
}

void _boot_window_test_draw(struct dwm_window *wnd, void *ctx) {
	ClearBackground(RAYWHITE);

	renderer_state_t *st = _ntRendererGetState();

	DrawText("test", 20 * st->scaling, 20 * st->scaling, 20 * st->scaling, BLACK);

	DrawFPS(st->scaling, st->scaling);

	struct dwm_context *dwmctx = (struct dwm_context *)ctx;
}

void _boot_begin_debug(void *user) {
	struct dwm_context *ctx = (struct dwm_context *)user;

	// check if F1 key is pressed
	if (IsKeyPressed(KEY_F1)) {
		// create window "Settings !"
		struct dwm_window wnd = _ntCreateWindow("Settings !", (Vector2){200, 300});

		// set position
		wnd.position = (Vector2){50, 50};

		wnd.draw = _boot_window_test_draw;

		// push window
		_ntPushWindow(ctx, wnd);
	}

	int c = GetCharPressed();

	while (c != 0) {
		RSBPopElementString(str_test);

		RSBAddElementString(str_test, c);
		RSBAddElementString(str_test, 0);

		c = GetCharPressed();
		// _boot_run_command("CTERM_line_execute", TextFormat("notify %s", str_test->objects));
		snprintf(str_test2, 2048, "notify %s", (const char *)str_test->objects);

		_boot_run_command("CTERM_line_execute", (void *)str_test2);
	}

	if (IsKeyPressed(KEY_BACKSPACE)) {
		RSBPopElementString(str_test);

		_boot_run_command("CTERM_line_execute", (void *)str_test2);
	}
}

#include <unistd.h>

bool _boot_run_logo() {
	bool result = true;
	
	#if SKIP_LOGO == 0
	result = _boot_run_command("logo", NULL);
	#endif

	return result;
}
bool _boot_run_msoobe(struct dwm_context *ctx) {
	bool result = _boot_run_command("msoobe", ctx);

	return result;
}
bool _boot_run_setup(struct dwm_context *ctx) {
	bool result = _boot_run_command("setup", ctx);
	
	return result;
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

	// init Text UI environment
	_ntRendererPushQueue(_ntTuiLoadEnvironmentDefault, NULL);

	// _boot_try_parse_explorer();
	
	struct dwm_context *ctx = _ntCreateDwmContext("ntresources/basic.theme");

	// for (int i = 0; i < 1; i++) {
	// 	int c = i * 50;

	// 	struct dwm_window wnd = _ntCreateWindow("Settings !", (Vector2){200 + c, 300});

	// 	wnd.position = (Vector2){50 + c, 50 + c};

	// 	_ntPushWindow(ctx, wnd);
	// }

	str_test = RSBCreateArrayString();
	str_test2 = (char *)calloc(1, 2048);

	renderer_state_t * st = _ntRendererGetState();

	st->layers[1].user = ctx;
	st->layers[1].update = _boot_begin_debug;

	_cterm_init();

	_ntDwmSetGlobal(ctx);

	bool logo_runned_before = false;
	
	#if SKIP_LOGO == 0
	WaitTime(1);
	#else
	WaitTime(0.02);
	#endif

	_boot_run_logo();
	
	// setup dwm layer
	st->layers[0].user = ctx;
	st->layers[0].draw = _ntDrawDwmContext;

	#if SKIP_LOGO == 0
	// wait 5.5 seconds
	WaitTime(5.5);

	logo_runned_before = true;
	#endif

	// set background opacity to be fully transparent
	ctx->theme.basic.background_color.a = 0x00;

	// move dwm layer to 2 so we will be able to create and manipulate windows inside oobe
	st->layers[2].user = ctx;
	st->layers[2].draw = st->layers[0].draw;

	st->layers[0].draw = NULL;

	if (!config.graphical_setup_completed) {
		// run setup with the dwm context
		_boot_run_setup(ctx);

		// wait 12.5 seconds
		WaitTime(12.5);
	}

	if (!config.oobe_completed) {
		if (!logo_runned_before && !SKIP_LOGO) {
			if (!_boot_run_logo()) return;

			// wait 5.5 seconds
			WaitTime(5.5);
		}

		_boot_run_msoobe(ctx);
	}

	for (;;) {
		_ntUnloadConfig(config);

		config = _ntGetConfig(config_path);

		if (config.oobe_completed) break;

		WaitTime(0.1);
	}

	_boot_run_command("logonui", NULL);

	WaitTime(0.1);

	for (int i = 0; i < 2; i++) {
		_boot_run_command("explorer", NULL);
	}
}
