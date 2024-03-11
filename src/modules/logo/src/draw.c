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

#include <nt5emul/modules/logo/state.h>
#include <nt5emul/version.h>

#include <nt5emul/renderer.h>

#ifndef NULL
#define NULL (void *)0
#endif

void logo_draw(void *user) {
    if (_state.old_layer.on_draw.callback) _state.old_layer.on_draw.callback(_state.old_layer.on_draw.user);

    renderer_state_t *st = _ntRendererGetState();

    int w = GetRenderWidth();
    int h = GetRenderHeight();

    DrawRectangle(0, 0, w, h, BLACK);

    float alignX = (w - (_state.logo_texture.width * st->scaling)) / 2;
    float alignY = (h - (_state.logo_texture.height * st->scaling)) / 2;

    // DrawTexture(_state.logo_texture, alignX * 1.1f, (int)(alignY) * 0.9f, _state.transition_color);
    DrawTextureEx(_state.logo_texture, (Vector2){
        alignX * 1.1f, (int)(alignY) * 0.9f
    }, 0.f, 1.f * st->scaling, _state.transition_color);

    const char *str = "Powered by raylib";
    int sz = 20 * st->scaling;

    Vector2 textsz = MeasureTextEx(GetFontDefault(), str, sz, 1.f * st->scaling);

    DrawText(str, (10 * st->scaling), h - textsz.y - (10 * st->scaling), sz, _state.transition_color);

    _ntRendererDrawWatermarkEx((Vector2){0, 0}, _state.transition_color);
}