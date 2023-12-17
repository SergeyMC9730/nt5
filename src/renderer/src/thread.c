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

void *_ntRendererThread(void *ptr) {
	// init raylib window
	InitWindow(640, 480, "NT5");

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

	// set status to READY
	st->status = RENDERER_READY;
	
	while (!WindowShouldClose()) {
		if (st->status & RENDERER_REQUESTED_STOP) break;

		// update renderer
		_ntRendererUpdate();

		// begin drawing
		BeginDrawing();

		// draw everything
		_ntRendererDraw();

		// complete drawing
		EndDrawing();
	}

	CloseWindow();

	return NULL;
}