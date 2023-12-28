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

#include <nt5emul/modules/oobe/render.h>

void _ntModOobeDrawStretchedTexture(Texture2D texture, bool x_stretched, bool y_stretched, float xstretchmul, float ysctretchmul, Vector2 pos, Vector2 origin) {
    Vector2 sz = {
        .x = GetRenderWidth(),
        .y = GetRenderHeight()
    };

    Rectangle source = {
        .x = 0,
        .y = 0,
        .width = texture.width,
        .height = texture.height
    };

    Rectangle dest = {
        .x = pos.x,
        .y = pos.y,
        .width = source.width,
        .height = source.height
    };

    if (x_stretched) {
        dest.width = sz.x * xstretchmul;
    }
    if (y_stretched) {
        dest.height = sz.y * ysctretchmul;
    }

    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}