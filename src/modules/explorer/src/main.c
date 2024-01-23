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
#include <nt5emul/dwm/context.h>

#include <stdio.h>

void _ntPVOnFileClick(struct nt_file_selector_menu *menu, const char *file_path) {
    printf("file_path=%s\n", file_path);
}

bool explorer_command(void *data) {
    // if (_state.execution_lock) {
    //     printf("error: only a single explorer process can be executed at the same time!\n");

    //     return false;
    // }

    // _state.execution_lock = true;

    renderer_state_t *st = _ntRendererGetState();

    if (_state.id == 0) {
        int index = 0;

        _state.old_draw = st->layers[index].draw;
        _state.old_update = st->layers[index].update;
        _state.old_ctx = st->layers[index].user;

        st->layers[index].draw = explorer_shell_draw;
        st->layers[index].update = explorer_shell_update;

        _state.id++;

        return true;
    }

    struct local_module_state *lst = (struct local_module_state *)calloc(1, sizeof(struct local_module_state));

    lst->fs = _ntLoadFileSelector("./", 10);

    _ntFileSelectorSetListing(lst->fs);
    _ntUpdateMenu(&lst->fs->base);
    
    lst->fs->base.x = 1;
    lst->fs->base.y = 1;
    lst->fs->callback = _ntPVOnFileClick;

    struct dwm_window wnd = _ntCreateWindow("Explorer", (Vector2){200, 300});
    wnd.draw = explorer_draw;
    wnd.upadte = explorer_update;
    wnd.ctx = lst;

    wnd.filled.state = false;
    wnd.filled.ability = false;

    wnd.position = (Vector2){50, 50};

    _ntPushWindow(_ntDwmGetGlobal(), wnd);

    _state.id++;

    return true;
}