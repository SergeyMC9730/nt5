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

// draw text
void _ntTuiDrawText(const char *str, unsigned char x, unsigned char y, Color col);

/*
    draw text centered
    
    if X equals to 0xFF then text would be centered by X;
    if Y equals to 0xFF then text would be centered by Y.

    in other cases x and y are gonna be position offsets.
*/
void _ntTuiDrawTextCentered(const char *str, signed char x, signed char y, Color col);