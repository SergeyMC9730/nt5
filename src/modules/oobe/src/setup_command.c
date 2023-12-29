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

#include <nt5emul/modules/oobe/setup_command.h>
#include <nt5emul/modules/oobe/state.h>
#include <nt5emul/modules/oobe/render.h>

#include <nt5emul/renderer.h>

#include <nt5emul/timer.h>

void setup_decrement_time(void *ctx) {
    _state.minutes_left -= 10;
}

bool setup_command(void *data) {
    renderer_state_t *st = _ntRendererGetState();

    int layer_index = 0;

    renderer_layer_t *layer = st->layers + layer_index;

    _state.old_draw = layer->draw;
    _state.old_update = layer->update;
    _state.old_ctx = layer->user;

    _state.dwm_ctx = data;

    int times = 4;

    _state.minutes_left = times * 10;

    for (int i = 0; i < times; i++) {
        _ntInstallTimer(setup_decrement_time, (float)times * (float)(i + 1));
    }

    layer->draw = draw_background;

    // load all textures before rendering oobe layer
    _ntRendererPushQueue(setup_preload, NULL);

    return true;
}