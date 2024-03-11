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
#include <nt5emul/version.h>

void _ntRendererDrawWatermark() {
    Color col = WHITE;
    col.a = 128;

    return _ntRendererDrawWatermarkEx((Vector2){0, 0}, col);
}

void _ntRendererDrawWatermarkEx(Vector2 offset, Color col) {
    const char *str = NT5_VERSION;
    renderer_state_t *st = _ntRendererGetState();
    int sz = 20 * st->scaling;

    int w = GetRenderWidth();
    int h = GetRenderHeight();

    Vector2 textsz2 = MeasureTextEx(GetFontDefault(), str, sz, 1.f * st->scaling);

    DrawText(str, w - textsz2.x - (20 * st->scaling * 1.5f) + offset.x, h - textsz2.y - (10 * st->scaling) + offset.y, sz, col);
}