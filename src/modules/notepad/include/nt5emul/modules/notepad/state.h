
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

#pragma once

#include <cterm/applications/api.h>

struct module_state {
    cterm_t *runtime;

    bool execution_lock;

    void (*old_draw)(void *user);
    void (*old_update)(void *user);
    void *old_ctx;
};

extern struct module_state _state;

struct local_notepad_module_state {
    int id;
};