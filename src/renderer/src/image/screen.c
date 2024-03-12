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

void _ntRendererDrawScreenPortion(Vector2 pos, Vector2 portion_pos, Vector2 portion_sz) {
    Rectangle source = {
        .x = portion_pos.x,
        .y = portion_pos.y,
        .width = portion_sz.x,
        .height = portion_sz.y * -1.f
    };

    Rectangle dest = {
        .x = pos.x,
        .y = pos.y,
        .width = portion_sz.x,
        .height = portion_sz.y
    };

    renderer_state_t *st = _ntRendererGetState();

    DrawTexturePro(st->framebuffer.texture, source, dest, (Vector2){}, 0.f, WHITE);
}