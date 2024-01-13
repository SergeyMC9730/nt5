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

#ifndef NULL
#define NULL (void *)0
#endif

void logo_draw(void *user) {
    if (_state.old_draw != NULL) _state.old_draw(_state.old_ctx);

    int w = GetRenderWidth();
    int h = GetRenderHeight();

    DrawRectangle(0, 0, w, h, BLACK);

    float alignX = (w - _state.logo_texture.width) / 2;
    float alignY = (h - _state.logo_texture.height) / 2;

    DrawTexture(_state.logo_texture, alignX * 1.1f, (int)(alignY) * 0.9f, _state.transition_color);

    const char *str = "Powered by raylib";
    int sz = 20;

    Vector2 textsz = MeasureTextEx(GetFontDefault(), str, sz, 1.f);

    DrawText(str, 10, h - textsz.y - 10, sz, _state.transition_color);

    const char *str2 = NT5_VERSION;

    Vector2 textsz2 = MeasureTextEx(GetFontDefault(), str2, sz, 1.f);

    DrawText(str2, w - textsz2.x - 20, h - textsz2.y - 10, sz, _state.transition_color);
}