
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

#include <nt5emul/modules/notepad/state.h>
#include <nt5emul/modules/notepad/notepad_command.h>
#include <nt5emul/dwm/context.h>
#include <nt5emul/dwm/window.h>


bool notepad_command(void *data) {
    
    
struct dwm_window wnd = _ntCreateWindow("notepad", (Vector2){500, 150});

    wnd.draw = notepad_draw;
    wnd.update = notepad_update;

    wnd.filled.state = true;
    wnd.filled.ability = true;

    wnd.position = (Vector2){50, 50};
    
    _ntPushWindow(_ntDwmGetGlobal(), wnd);


    return true;
}

void notepad_draw(struct dwm_window *wnd, void *ctx) {
    
}

void notepad_update(struct dwm_window *wnd, void *ctx) {
    
}
