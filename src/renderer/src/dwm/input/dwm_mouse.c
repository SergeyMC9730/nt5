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

#include <nt5emul/dwm/context.h>

// get local mouse position inside the dwm context
Vector2 _ntDwmGetLocalMousePosition(struct dwm_context *ctx) {
    if (ctx->rendered_window == NULL) return GetMousePosition();

    Vector2 m = GetMousePosition();
    m.x -= ctx->rendered_window->position.x;
    m.y -= ctx->rendered_window->position.y + ctx->rendered_window->titlebar_rect.height + 4;

    return m;
}