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

// set window scale
Vector2 _ntRendererSetDpiScale(float scale) {
    renderer_state_t *st = _ntRendererGetState();

    float old_scale = st->scaling;

    if (old_scale <= 0.f) old_scale = 1.f;

    Vector2 sz = st->current_window_size;
    sz = st->current_window_size;
    sz = st->current_window_size;
    sz = st->current_window_size;

    sz.x /= old_scale;
    sz.y /= old_scale;

    Vector2 new_sz = sz;
    new_sz.x *= scale;
    new_sz.y *= scale;

    printf("current wsize: %f %f\n", st->current_window_size.x, st->current_window_size.y);
    printf("wsize in stack: %f %f\n", sz.x, sz.y);
    printf("scale val: %f\n", scale);
    printf("old scale val: %f\n", old_scale);
    printf("setting size to %f %f\n", new_sz.x, new_sz.y);

    SetTextLineSpacing((int)(15.f * scale / 2.f));

    _ntRendererSetWindowSize((Vector2){new_sz.x, new_sz.y});

    if (st->framebuffer.texture.width == 0 || st->framebuffer.texture.height == 0) {
        st->scaling = scale;
        
        return new_sz;
    }

    int idx = _ntRendererGetMainIdxInStack();

    UnloadRenderTexture(st->framebuffer);

    st->framebuffer = LoadRenderTexture(new_sz.x, new_sz.y);

    if (idx != -1) {
        st->r2dstack[idx] = st->r2dstack[idx] = st->framebuffer;
    }

    st->scaling = scale;

    return new_sz;
}
