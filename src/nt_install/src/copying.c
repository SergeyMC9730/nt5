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


#include <nt5emul/tui/frame.h>
#include <nt5emul/tui/rectangle.h>
#include <nt5emul/tui/text.h>
#include <nt5emul/tui/input.h>
#include <nt5emul/tui/progress_bar.h>

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <string.h>
#include <stdio.h>

#include <nt5emul/bi/cabinet.h>
#include <nt5emul/timer.h>

#include <sys/stat.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_thread8() {
    size_t l = __state.cabfile_list->len;
    size_t i = 0;

    // create folders
    mkdir("nt/sounds", 0777);

    mkdir("nt/images", 0777);
    mkdir("nt/images/user", 0777);
    mkdir("nt/images/user/avatars", 0777);
    mkdir("nt/images/user/wallpapers", 0777);
    mkdir("nt/images/user/ad", 0777);
    mkdir("nt/images/user/ui", 0777);

    mkdir("nt/images/system", 0777);

    mkdir("nt/images/placeholders", 0777);
    
    mkdir("nt/binary", 0777);

    mkdir("nt/fonts", 0777);

    mkdir("nt/videos", 0777);
    mkdir("nt/videos/user", 0777);

    while (i < l) {
        // get cabinet by index
        struct cabfile c = RSBGetAtIndexcabfile(__state.cabfile_list, i);

        snprintf(__state.buffers[4], 128, "%s/%s", __state.buffers[7], c.cabinet_path);

        // extract cabinet file
        _boot_install_extract_cabinet(c.cabinet_path, __state.buffers[4]);

        // calculate progress
        __state.timer0 = (float)i / (float)l;

        i++;
    }

    // convert title.wma to title.mp3

    system("ffmpeg -i nt/sounds/title.wma -b:a 256K nt/sounds/title.mp3");

    _boot_install_beginstep9();
}

void _boot_install_update_step8_1() {
    int szX = GetRenderWidth() / __state.base_size.x;

    int sz = 1024;

    memset(__state.buffers[5], 0, sz);

    // |Copying: %s
    snprintf(__state.buffers[6], sz, __boot_install_strings[50], __state.cabfile_current_file);

    int spaces = szX - __state.max_cabfile_length - strlen(__boot_install_strings[50]);
    int i = 0;

    while (i < spaces) {
        strcat(__state.buffers[5], " ");

        i++;
    }

    strcat(__state.buffers[5], __state.buffers[6]);
}

void _boot_install_update_step8() {
    __state.cabfile_current_file = "";
    __state.status_bar_label = __state.buffers[5];

    _ntInstallTimer(_boot_install_thread8, 0.1f, NULL);

    _renderer_state.layers[1].update = _boot_install_update_step8_1;
}

void _boot_install_draw_step8() {
    Rectangle r;
    r.width = 40;
    r.height = 2;
    r.x = 10;
    r.y = 10;

    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};
    Color blue = (Color){0x00, 0x09, 0xAB, 0xFF};

    // get render size in characters
    int szX = GetRenderWidth() / __state.base_size.x;
    int szY = GetRenderHeight() / __state.base_size.y;

    // Please wait while Setup copies files
    _ntTuiDrawTextCentered(__boot_install_strings[46], 0xFF, 5, gray);
    // to the Windows installation folders.
    _ntTuiDrawTextCentered(__boot_install_strings[47], 0xFF, 6, gray);
    // This might take several minutes to complete.
    _ntTuiDrawTextCentered(__boot_install_strings[48], 0xFF, 7, gray);

    // get percentage of timer
    float p = __state.timer0 * 100.f;

    // format string
    snprintf(__state.buffers[3], 64, "%d%c", (int)p, '%');

    int offset = 7;

    // generate frame 1
    r.width = szX - (offset * 2);
    r.height = 6;
    r.x = offset - 1;
    r.y = (szY - r.height) / 2 + 1;

    //  Setup is copying files...
    _ntTuiDrawFrameDouble(r, gray, __boot_install_strings[49]);

    offset += 5;

    // generate frame 2
    r.width = szX - (offset * 2);
    r.height = 2;
    r.x = offset - 1;
    r.y += 3;

    // draw second frame
    _ntTuiDrawFrame(r, gray, NULL);

    // generate progress bar rectangle

    offset++;

    r.width = szX - (offset * 2);
    r.height = 1;
    r.x = offset - 1;
    r.y++;

    _ntTuiDrawProgressBar(__state.timer0 * 100.f, r, blue, YELLOW);

    _ntTuiDrawTextCentered(__state.buffers[3], 0xFF, r.y - 2, gray);
}