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

#include <nt5emul/modules/explorer/intro.h>
#include <nt5emul/modules/explorer/local_state.h>

#include <nt5emul/dwm/window.h>
#include <nt5emul/dwm/context.h>

void explorer_intro_create() {
    struct local_module_state *lst = (struct local_module_state *)calloc(1, sizeof(struct local_module_state));

    struct dwm_window wnd = _ntCreateWindow("Intro", (Vector2){500, 150});
    wnd.draw = explorer_intro_draw;
    wnd.on_close = explorer_intro_on_close;
    wnd.ctx = lst;

    wnd.filled.state = true;
    wnd.filled.ability = true;

    wnd.position = (Vector2){50, 50};

    _ntDwmPushWindow(_ntDwmGetGlobal(), wnd);
}