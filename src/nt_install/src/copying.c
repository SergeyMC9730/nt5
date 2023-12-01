#include <nt5emul/bi/frame.h>
#include <nt5emul/bi/rectangle.h>
#include <nt5emul/bi/text.h>
#include <nt5emul/bi/input.h>
#include <nt5emul/bi/progress_bar.h>

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <string.h>
#include <stdio.h>

#include <nt5emul/bi/cabinet.h>
#include <nt5emul/bi/timer.h>

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

    _boot_install_timer(_boot_install_thread8, 0.1f);

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
    _biTextDrawCentered(__boot_install_strings[46], 0xFF, 5, gray);
    // to the Windows installation folders.
    _biTextDrawCentered(__boot_install_strings[47], 0xFF, 6, gray);
    // This might take several minutes to complete.
    _biTextDrawCentered(__boot_install_strings[48], 0xFF, 7, gray);

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
    _biDrawFrameDouble(r, gray, __boot_install_strings[49]);

    offset += 5;

    // generate frame 2
    r.width = szX - (offset * 2);
    r.height = 2;
    r.x = offset - 1;
    r.y += 3;

    // draw second frame
    _biDrawFrame(r, gray, NULL);

    // generate progress bar rectangle

    offset++;

    r.width = szX - (offset * 2);
    r.height = 1;
    r.x = offset - 1;
    r.y++;

    _biDrawProgressBar(__state.timer0 * 100.f, r, blue, YELLOW);

    _biTextDrawCentered(__state.buffers[3], 0xFF, r.y - 2, gray);
}