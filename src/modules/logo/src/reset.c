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
#include <nt5emul/renderer.h>

void logo_unload_textures(void *ctx) {
    UnloadTexture(_state.logo_texture);
}

void logo_reset() {
    renderer_state_t *st = _ntRendererGetState();

    int index = RENDERER_LAYERS - 2;

    st->layers[index] = _state.old_layer;

    _ntRendererPushQueue(logo_unload_textures, NULL);

    _state.init_complete = false;
    _state.execution_lock = false;

    SetWindowSize(_state.old_window_size.x, _state.old_window_size.y);
}