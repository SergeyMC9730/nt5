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

void BeginTextureModeStacked(RenderTexture2D txt) {
    renderer_state_t *st = _ntRendererGetState();

    if (st->r2dpointer > R2D_STACK_SIZE - 1 || st->r2dpointer < 0) {
        return BeginTextureMode(txt);
    }

    st->r2dstack[st->r2dpointer] = txt;

    if (st->r2dpointer >= 1) EndTextureMode();

    st->r2dpointer++;

    BeginTextureMode(txt);
}