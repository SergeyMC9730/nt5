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

#include <nt5emul/arrays/rsb_array_int.h>
#include <stdio.h>

RSB_ARRAY_IMPL_GEN(int, Int)

void RSBPrintArrayInt(rsb_array_Int *array) {
    for (int i = 0; i < array->len; i++) {
        int obj = RSBGetAtIndexInt(array, i);

        printf("%d ", obj);
    }
}