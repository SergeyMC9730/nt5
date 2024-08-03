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

#include <nt5emul/renderer.h>

// set window size
// also modifies renderer state
struct resize_request {
    int x;
    int y;
};

void _ntRendererSetWindowSizeCallback(struct resize_request *req) {
    renderer_state_t *st = _ntRendererGetState();

    UnloadRenderTexture(st->framebuffer);
    st->framebuffer = LoadRenderTexture(req->x, req->y);

    free(req);
}

#define CTERM_FPTR_CAST(ret, ...) ret (*)(__VA_ARGS__)

void _ntRendererSetWindowSize(Vector2 size) {
    renderer_state_t *st = _ntRendererGetState();

    float mul = 1.f;

    if (st->fake_scaling){ 
        mul = GetWindowScaleDPI().x;
        // size.x /= mul;
        // size.y /= mul;
    } else {
        SetWindowSize(size.x, size.y);
    }

    struct resize_request *request = (struct resize_request *)(MemAlloc(sizeof(struct resize_request)));
    request->x = size.x;
    request->y = size.y;

    _ntRendererPushQueue((CTERM_FPTR_CAST(void, void *))(_ntRendererSetWindowSizeCallback), request);

    st->current_window_size = size;
}