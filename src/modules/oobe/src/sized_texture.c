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

void _ntModOobeDrawSizedTexture(Texture2D texture, Vector2 size, Vector2 pos, Vector2 origin) {
    Rectangle source = {
        .x = 0,
        .y = 0,
        .width = texture.width * (1.f / size.x),
        .height = texture.height * (1.f / size.y)
    };

    Rectangle dest = {
        .x = pos.x,
        .y = pos.y,
        .width = texture.width,
        .height = texture.height
    };

    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}