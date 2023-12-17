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

#include <raylib.h>

// draw frame with default character mapping
// `description` can be NULL, in this case text would not be displayed
void _ntTuiDrawFrame(Rectangle r, Color col, const char *description);

// draw frame with double lines
// `description` can be NULL, In this case text would be displayed
void _ntTuiDrawFrameDouble(Rectangle r, Color col, const char *description);

// draw frame with custom character mapping
// `mapping` contains an array with 7 strings. each one contains frame element.
// see `mapping` example in `interface_frame.c:61`
// `description` can be NULL, in this case text would not be displayed
void _ntTuiDrawFrameEx(Rectangle r, Color col, const char **mapping, const char *description);