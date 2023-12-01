#include <nt5emul/bi/frame.h>
#include <nt5emul/bi/rectangle.h>
#include <nt5emul/bi/text.h>
#include <nt5emul/bi/input.h>
#include <nt5emul/bi/progress_bar.h>

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <string.h>
#include <stdio.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

void _boot_install_update_step7() {
    float delta = GetFrameTime();

    __state.timer0 += delta;

    if (__state.timer0 >= 1.f) {
        __state.timer0 = 0.f;
        _boot_install_beginstep8();
    }
}

void _boot_install_draw_step7() {
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

    // Please wait until Setup formats the partition
    _biTextDrawCentered(__boot_install_strings[25], 0xFF, 5, gray);
    _biTextDrawCentered(__state.buffers[4], 0xFF, 7, gray);

    // get percentage of timer
    float p = __state.timer0 * 100.f;

    // format string
    snprintf(__state.buffers[3], 64, "%d%c", (int)p, '%');

    int offset = 7;

    // generate frame 1
    r.width = szX - (offset * 2);
    r.height = 6;
    r.x = offset - 1;
    r.y = szY - 11;

    //  Setup is formating...
    _biDrawFrameDouble(r, gray, __boot_install_strings[44]);

    offset += 5;

    // generate frame 2
    r.width = szX - (offset * 2);
    r.height = 2;
    r.x = offset - 1;
    r.y = szY - 8;

    // draw second frame
    _biDrawFrame(r, gray, NULL);

    // generate progress bar rectangle

    offset++;

    r.width = szX - (offset * 2);
    r.height = 1;
    r.x = offset - 1;
    r.y = szY - 7;

    _biDrawProgressBar(__state.timer0 * 100.f, r, blue, YELLOW);

    _biTextDrawCentered(__state.buffers[3], 0xFF, r.y - 2, gray);
}