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

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// STEP 8

extern void _boot_install_update_step8();
extern void _boot_install_draw_step8();

// expose NT renderer
extern renderer_state_t _renderer_state;

// https://en.cppreference.com/w/c/algorithm/qsort
int _boot_install_compare8(const void *a, const void *b) {
    const int arg1 = *(const int *)a;
    const int arg2 = *(const int *)b;
 
    if (arg1 > arg2) return -1;
    if (arg1 < arg2) return 1;

    return 0;

}

void _boot_install_beginstep8() {
    _renderer_state.layers[1].on_update.callback = _boot_install_update_step8;
    _renderer_state.layers[1].on_draw.callback = _boot_install_draw_step8;

    size_t cl =  __state.cabfile_list->len;
    size_t fl = 0;

    // get amount of all files in all cabinets
    size_t i = 0;
    while (i < cl) {
        // get cabinet by index
        struct cabfile c = RSBGetAtIndexcabfile(__state.cabfile_list, i);

        // add amount of files into fl
        fl += c.files->len;

        i++;
    }

    // allocate an array for those files
    int *lengths = (int *)MemAlloc(sizeof(int) * fl);

    // add filename lengths into this array
    i = 0;
    while (i < cl) {
        // get cabinet by index
        struct cabfile c = RSBGetAtIndexcabfile(__state.cabfile_list, i);

        // go through each file
        size_t j = 0;
        while (j < c.files->len) {
            // get file
            struct cabfile_file f = RSBGetAtIndexcabfile_file_array(c.files, j);

            // add length
            lengths[i + j] = strlen(f.internal_name);

            j++;
        }

        i++;
    }

    // sort an array; from the highest value to the lowest
    qsort(lengths, fl, sizeof(int), _boot_install_compare8);

    __state.max_cabfile_length = lengths[0];

    // free array
    MemFree(lengths);

    renderer_state_t *st = _ntRendererGetState();

    // get render width in characters
    int szX = st->current_window_size.x / __state.base_size.x;

    // reallocate buffer 4
    __state.buffers[4] = MemRealloc(__state.buffers[4], szX);
    // reset buffer
    memset(__state.buffers[4], 0, szX);

    int sz = 1024;

    // allocate buffer 5
    __state.buffers[5] = MemAlloc(sz);
    // reset buffer
    memset(__state.buffers[5], 0, sz);

    // allocate buffer 6
    __state.buffers[6] = MemAlloc(sz);
    // reset buffer
    memset(__state.buffers[6], 0, sz);

    // allocate buffer 8
    __state.buffers[8] = MemAlloc(sz);
    // reset buffer
    memset(__state.buffers[8], 0, sz);
}