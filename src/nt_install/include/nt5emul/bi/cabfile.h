/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  SergeyMC9730

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

    Contact SergeyMC9730 -- @dogotrigger in Discord
*/

#pragma once

#include <stddef.h>

#include <nt5emul/arrays/rsb_array_gen.h>

struct cabfile_file {
    const char *internal_name;
    const char *destination_path;
};

RSB_ARRAY_DEF_GEN(struct cabfile_file, cabfile_file_array);

struct cabfile {
    const char *cabinet_path;
    rsb_array_cabfile_file_array *files;
};

RSB_ARRAY_DEF_GEN(struct cabfile, cabfile);