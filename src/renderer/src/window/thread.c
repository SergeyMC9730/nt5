/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  SergeyMC9730

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

    Contact SergeyMC9730 -- @dogotrigger in Discord
*/

#include <nt5emul/renderer.h>

#include <raylib.h>

#include <string.h>

#include <sys/types.h>
#include <stdio.h>

void *_ntRendererThread(void *ptr) {
	Vector2 wsz = {
		640, 480
	};

	// set highdpi
	SetWindowState(FLAG_WINDOW_HIGHDPI);

	// init raylib window
	InitWindow(wsz.x, wsz.y, "NT5");

	while (!IsWindowReady()) {}

	// get renderer state
	renderer_state_t *st = _ntRendererGetState();

	bool fake_scaling = st->fake_scaling;

	st->current_window_size = wsz;

	// check if layers already exists and free if they
	if (st->layers != NULL) {
		MemFree(st->layers);
	}

	// calculate layer array size
	int layers_size = sizeof(renderer_layer_t) * RENDERER_LAYERS;

	// allocate array
	st->layers = (renderer_layer_t *)(MemAlloc(layers_size));

	// make it empty
	memset(st->layers, 0, layers_size);

	// set window fps to main monitor's refresh rate
	SetTargetFPS(GetMonitorRefreshRate(0));

	// get window scaling
	float _scaling = GetWindowScaleDPI().x;

	if (!fake_scaling) {
		wsz = _ntRendererSetDpiScale(_scaling);
	} else {
		wsz.x *= _scaling;
		wsz.y *= _scaling;

		st->scaling = 1.f;
	}

	SetWindowSize(wsz.x, wsz.y);

	// set window to be top most.
	// useful during debugging;
	SetWindowState(FLAG_WINDOW_TOPMOST);

	// load framebuffer
	RenderTexture2D rt1 = LoadRenderTexture(wsz.x / _scaling, wsz.y / _scaling);
	st->framebuffer = rt1;

	RenderTexture2D rt2;
	if (fake_scaling) {
		// create helper framebuffer

		rt2 = LoadRenderTexture(wsz.x, wsz.y);
	}

	// set status to READY
	st->status = RENDERER_READY;

	bool raylib_close = false;

	bool show_real_fb = false;
	
	while (true) {
		raylib_close = WindowShouldClose();

		if (IsKeyPressed(KEY_PRINT_SCREEN)) {
			show_real_fb = !show_real_fb;
		}

		// printf("fake_scaling=%d\n", fake_scaling);

		// update renderer
		_ntRendererUpdate();

		if (GetRenderWidth() != wsz.x || GetRenderHeight() != wsz.y) {
			wsz.x = GetRenderWidth();
			wsz.y = GetRenderHeight();

			UnloadRenderTexture(rt1);
			rt1 = LoadRenderTexture(wsz.x, wsz.y);
			st->framebuffer = rt1;
		}

		if (st->status & RENDERER_REQUESTED_STOP || raylib_close) break;

		// draw everything into the internal framebuffer
		BeginTextureModeStacked(st->framebuffer);

		// begin drawing
		BeginDrawing();

		ClearBackground(BLACK);

		// draw everything
		_ntRendererDraw();

		// end
		EndTextureModeStacked();

		if (fake_scaling) {
			// now draw internal framebuffer to the screen

			if (fake_scaling && show_real_fb) {
				_ntRendererDrawSizedTexture(st->framebuffer.texture, (Vector2){1, -1}, (Vector2){}, (Vector2){}, true);
			}
			if (fake_scaling && !show_real_fb) {
				BeginTextureModeStacked(rt2);
				ClearBackground(BLACK);
				_ntRendererDrawStretchedTexture(st->framebuffer.texture, true, true, _scaling * 2, _scaling * 2, (Vector2){0, -st->current_window_size.y * _scaling}, (Vector2){});
				EndTextureModeStacked();
				_ntRendererDrawSizedTexture(rt2.texture, (Vector2){1, 1}, (Vector2){}, (Vector2){}, true);
			}

		} else {
			_ntRendererDrawSizedTexture(st->framebuffer.texture, (Vector2){1, -1}, (Vector2){}, (Vector2){}, true);
		}

		// complete drawing
		EndDrawing();
	}


	// unload rendertextures
	UnloadRenderTexture(st->framebuffer);

	if (fake_scaling) {
		UnloadRenderTexture(rt2);
	}

	if (raylib_close) {
		_ntRendererCloseEnvironment();
	} else {
		printf("close the window!!!\n");
		CloseWindow();
	}

	printf("close the window! 2!!\n");

	return NULL;
}

bool _ntRendererInThread() {
	// get thread id
	pthread_t p = pthread_self();

	// get renderer state
	renderer_state_t *st = _ntRendererGetState();

	if (p == st->thread) return true;

	return false;
}