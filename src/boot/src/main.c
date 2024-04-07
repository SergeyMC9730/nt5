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

#include <nt5emul/ntcore.h>
#include <nt5emul/timer.h>

#define SKIP_LOGO 0


rsb_array_String *str_test;
char *str_test2;

bool _boot_run_command(const char *command, void *userdata) {
	// printf("running command %s\n", command);
	// load bootscreen
	cterm_command_reference_t ref = cterm_find_command((char *)command);

	// check if bootscreen module exist
	if (ref.callback) {
		// run it
		ref.callback(userdata);

		return true;
	}

	return false;
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

bool __boot_ended = false;

void _system_end(void *ctx) {
	if (__boot_ended) return;

	renderer_state_t * st = _ntRendererGetState();

	RSBDestroyEvent(st->close_events);
	
	exit(0);
}

#include <string.h>

void _boot_display_help() {
	const char *help_table[] = {
		"--skip-logo", "skip XP logo",
		"--skip-text-installation", "skip text-based installation process",
		"--skip-logonui", "skip logonui",
		"--set-2x-scale", "set window scale to be 2x",
		"--help", "display help",
		"-h", "display help"
	};

	int sz = sizeof(help_table) / sizeof(const char *);

	printf("@ help\n\n");

	if ((sz % 2) == 1) {
		printf("! help cannot be displayed: table size is not even !\n");

		return;
	}

	for (int i = 0; i < sz; i += 2) {
		printf("? %s : %s\n", help_table[i], help_table[i + 1]);
	}

	return;
}

#include <nt5emul/version.h>
#include <time.h>

void _boot_set2xscale(void *ctx) {
	_ntRendererSetDpiScale(2.0f);
}

void _boot_begin(int argc, char **argv) {
	clock_t _cl_start = clock();

	printf("! NT5 Project (%s)\n! Made by SergeyMC9730\n! Powered by raylib\n\n", NT5_VERSION);

	bool skip_logo = false;
	bool skip_text_installation = false;
	bool skip_logonui = false;
	bool display_help = false;
	bool set2xscale = false;
	
	if (argc >= 2) {
		int count = argc - 1;

		for (int i = 0; i < count; i++) {
			const char *value = (const char *)argv[i + 1];

			if (!strcmp(value, "--skip-logo")) {
				skip_logo = true;
			}
			else if (!strcmp(value, "--skip-text-installation")) {
				skip_text_installation = true;
			}
			else if (!strcmp(value, "--skip-logonui")) {
				skip_logonui = true;
			}
			else if (!strcmp(value, "--set-2x-scale")) {
				set2xscale = true;
			}
			else if (!strcmp(value, "--help")) {
				display_help = true;
			}
			else if (!strcmp(value, "-h")) {
				display_help = true;
			}
			else {
				printf("! invalid argument \"%s\". see --help\n", value);

				return;
			}
		}
	}

	if (display_help) {
		_boot_display_help();

		exit(0);
	}

	// create "nt" folder
	mkdir("nt", 0777);
	
	const char *config_path = "nt/config.json";

	struct nt_config config = _ntGetConfig(config_path);

	printf("config values: setup: %d; oobe; %d\n", config.setup_completed, config.oobe_completed);

	if (!config.setup_completed && !skip_text_installation) {
		_ntInitCores();

		// init NT renderer
		_ntRendererCreateEnvironment();

		if (set2xscale) {
			_ntRendererPushQueue(_boot_set2xscale, NULL);
			renderer_state_t * st = _ntRendererGetState();

			while (st->scaling != 2.f) {
				_ntSetupTimerSync(0.01);
			}
		}

		_ntRendererAddCloseEvent(_ntCloseCores, NULL, false);
		_ntRendererAddCloseEvent(_system_end, NULL, true);
		
		_boot_install_begin();

		return;
	}

	str_test = RSBCreateArrayString();
	str_test2 = (char *)calloc(1, 2048);

	renderer_state_t * st = _ntRendererGetState();

	_cterm_init();

	_ntInitCores();

	// init NT renderer
	_ntRendererCreateEnvironment();

	if (set2xscale) {
		_ntRendererPushQueue(_boot_set2xscale, NULL);

		while (st->scaling != 2.f) {
			_ntSetupTimerSync(0.01);
		}
	}

	_ntRendererAddCloseEvent(_ntCloseCores, NULL, false);
	_ntRendererAddCloseEvent(_system_end, NULL, true);

	// init Text UI environment
	_ntRendererPushQueue(_ntTuiLoadEnvironmentDefault, NULL);
	
	struct dwm_context *ctx = _ntDwmCreateContext("ntresources/basic.theme");

	_ntDwmSetGlobal(ctx);

	while (_cterm_ready != true) {
		_ntSetupTimerSync(0.01);
	}

	printf("argc=%d\n", argc);

	bool logo_runned_before = false;

	if (!skip_logo) {
		_ntDwmSetSize(ctx, (Vector2){GetRenderWidth(), GetRenderHeight()});

		_ntSetupTimerSync(1);
		_boot_run_logo();
	} else {
		// _ntSetupTimerSync(0.1);
	}
	
	// setup dwm layer
	st->layers[0].on_draw.user = ctx;
	st->layers[0].on_draw.callback = _ntDwmDrawContext;

	if (!skip_logo){
		// wait 5.5 seconds
		_ntSetupTimerSync(5.5);

		logo_runned_before = true;
	}

	// set background opacity to be fully transparent
	ctx->theme.basic.background_color.a = 0x00;

	// move dwm layer to 2 so we will be able to create and manipulate windows inside oobe
	st->layers[2].on_draw.user = ctx;
	st->layers[2].on_draw.callback = st->layers[0].on_draw.callback;

	st->layers[0].on_draw.callback = NULL;

	_ntDwmSetSize(ctx, (Vector2){GetRenderWidth(), GetRenderHeight()});

	if (!config.graphical_setup_completed) {
		// run setup with the dwm context
		_boot_run_setup(ctx);

		// wait 12.5 seconds
		_ntSetupTimerSync(12.5);
	}

	if (!config.oobe_completed) {
		if (!logo_runned_before && !skip_logo) {
			if (!_boot_run_logo()) return;

			// wait 5.5 seconds
			_ntSetupTimerSync(5.5);
		}

		_boot_run_msoobe(ctx);

		for (;;) {
			_ntUnloadConfig(config);

			config = _ntGetConfig(config_path);

			if (config.oobe_completed) break;

			_ntSetupTimerSync(0.1);
		}
	}

	if (!skip_logonui) {
		_boot_run_command("logonui", NULL);

		_ntSetupTimerSync(0.1);
	}

	for (int i = 0; i < 2; i++) {
		_boot_run_command("explorer", NULL);
		// _ntSetupTimerSync(0.2);
	}

	__boot_ended = true;

	clock_t _cl_end = clock();

	printf("elapsed: %f seconds\n", (double)(_cl_end - _cl_start) / CLOCKS_PER_SEC);
}