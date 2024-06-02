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
#include <nt5emul/modules/explorer/intro.h>
#include <nt5emul/modules/explorer/command.h>
#include <nt5emul/modules/explorer/shell.h>
#include <nt5emul/modules/explorer/window.h>
#include <nt5emul/modules/explorer/text.h>
#include <nt5emul/renderer.h>
#include <nt5emul/timer.h>
#include <nt5emul/dwm/context.h>
#include <nt5emul/dwm/window.h>
#include <nt5emul/nt_config.h>

#include <stdio.h>

#include <nt5emul/panic/setup.h>

bool explorer_command(void *data) {
    _ntPanic("idk", 1234);

    return false;

    load_text();

    renderer_state_t *st = _ntRendererGetState();

    if (_state.id == 0) {
        int index = 0;

        _state.old_layer = st->layers[index];

        st->layers[index].on_draw.callback = explorer_shell_draw;
        st->layers[index].on_update.callback = explorer_shell_update;

        _state.icon_pressed_id = -1;

        _state.id++;

        explorer_shell_init();

        explorer_intro_create();

        return true;
    }

    explorer_window_create();

    _state.id++;

    return true;
}
