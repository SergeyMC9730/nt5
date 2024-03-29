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
		640 * 2, 480 * 2
	};

	// set highdpi
	SetWindowState(FLAG_WINDOW_HIGHDPI);

	// init raylib window
	InitWindow(wsz.x, wsz.y, "NT5");

	// get renderer state
	renderer_state_t *st = _ntRendererGetState();

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

	st->scaling = GetWindowScaleDPI().x;

	wsz.x *= st->scaling;
	wsz.y *= st->scaling;

	SetWindowSize(wsz.x, wsz.y);

	// set window to be top most.
	// useful during debugging;
	// SetWindowState(FLAG_WINDOW_TOPMOST);

	// load framebuffer
	RenderTexture2D rt1 = LoadRenderTexture(wsz.x, wsz.y);
	st->framebuffer = rt1;
	
	// set status to READY
	st->status = RENDERER_READY;

	bool raylib_close = false;
	
	while (true) {
		raylib_close = WindowShouldClose();

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
		BeginTextureModeStacked(rt1);

		// begin drawing
		BeginDrawing();

		// draw everything
		_ntRendererDraw();

		// end
		EndTextureModeStacked();

		// now draw internal framebuffer to the screen
		_ntRendererDrawSizedTexture(rt1.texture, (Vector2){1, -1}, (Vector2){}, (Vector2){}, true);

		// complete drawing
		EndDrawing();
	}

	// unload rendertextures
	UnloadRenderTexture(rt1);

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