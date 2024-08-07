
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

struct cterm_instance;

#include <stdbool.h>

struct module_state {
    struct cterm_instance *runtime;

    bool execution_lock;

    void (*old_draw)(void *user);
    void (*old_update)(void *user);
    void *old_ctx;
};

extern struct module_state _state;

// #include <nt5emul/arrays/rsb_array_char.h>
typedef struct rsb_array_String rsb_array_String;

struct local_notepad_module_state {
    int id;

    rsb_array_String *file_contents;
    rsb_array_String *rendered_file_contents;

    char *file_path;
    char *file_name;

    char *title;

    const char *cterm_notepad_title;
    const char *cterm_notepad_untitled;
};