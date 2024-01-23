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

#include <nt5emul/modules/explorer/state.h>
#include <nt5emul/modules/explorer/explorer_command.h>
#include <nt5emul/renderer.h>
#include <nt5emul/timer.h>

#include <stdio.h>

bool explorer_command(void *data) {
    if (_state.execution_lock) {
        printf("error: only a single explorer process can be executed at the same time!\n");

        return false;
    }

    _state.execution_lock = true;

    renderer_state_t *st = _ntRendererGetState();

    int index = RENDERER_LAYERS - 2;

    _state.old_draw = st->layers[index].draw;
    _state.old_update = st->layers[index].update;
    _state.old_ctx = st->layers[index].user;

    st->layers[index].draw = explorer_draw;
    st->layers[index].update = explorer_update;

    return true;
}