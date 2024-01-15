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

#ifndef NULL
#define NULL (void *)0
#endif

void logo_update(void *user) {
    if (_state.old_update != NULL) _state.old_update(_state.old_ctx);

    if (!_state.init_complete) {
        _state.logo_texture = LoadTexture("nt/images/system/win32.bmp");
        _state.init_complete = true;

        renderer_state_t *st = _ntRendererGetState();

        SetWindowSize(640 * st->scaling, 480 * st->scaling);
    }

    int frames_per_step = GetFPS() / 60;
    int col_step = 1;
    if (frames_per_step == 0) {
        frames_per_step = 1;
        col_step = 60 / GetFPS();
    }

    int max_val = 0xFF + 1 - col_step;

    if (
        (_state.transition_color.a != max_val && _state.transition_color.a != 0xFF) && 
        !(_state.frames % frames_per_step)
    ) {
        _state.transition_color.a += col_step;
    }

    if (_state.transition_color.a == max_val) {
        _state.transition_color.a = 0xFF;
    }

    _state.frames++;
}