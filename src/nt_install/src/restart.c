#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>
#include <nt5emul/timer.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <nt5emul/tui/text.h>
#include <nt5emul/tui/frame.h>
#include <nt5emul/tui/progress_bar.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

void _boot_install_close() {
    // free buffer 0
    if (__state.buffers[0] != NULL) {
        MemFree(__state.buffers[0]);
        __state.buffers[0] = NULL;
    }

    // free buffer 3
    if (__state.buffers[3] != NULL) {
        MemFree(__state.buffers[3]);
        __state.buffers[3] = NULL;
    }

    // free cabfile list and its children
    if (__state.cabfile_list != NULL) {
        size_t i = 0;
        size_t l1 = __state.cabfile_list->len;

        while (i < l1) {
            // get cabfile
            struct cabfile c = RSBGetAtIndexcabfile(__state.cabfile_list, i);

            // free file array of an cabfile instance
            RSBDestroycabfile_file_array(c.files);

            i++;
        }

        // free cabfile
        RSBDestroycabfile(__state.cabfile_list);
        __state.cabfile_list = NULL;
    }

    system("(./nt5 &) &> /dev/null");

    // close renderer
    _ntRendererCloseEnvironment();
}

void _ntInstallTimer10() {
    __state.timer1++;

    // close nt5 when ENTER is pressed or timer == 15
    if (__state.timer1 == 15 || __state.halt) {
        _boot_install_close();
    }

    // loop
    _ntInstallTimer(_ntInstallTimer10, 1.f);
}

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_update_step10() {
    // close nt5 on ENTER
    if (IsKeyPressed(KEY_ENTER)) {
        __state.halt = true;
    }
}

void _boot_install_draw_step10() {
    if (__state.halt) return;
 
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

    // restart information
    _ntTuiDrawText(__boot_install_strings[52], 3, 4, gray);

    // get percentage of timer
    float p = (float)__state.timer1 / 15.f * 100.f;

    // format string
    if (__state.buffers[3] != NULL) snprintf(__state.buffers[3], 128, __boot_install_strings[53], 15 - __state.timer1);

    int offset = 7;

    // generate frame 1
    r.width = szX - (offset * 2);
    r.height = 6;
    r.x = offset - 1;
    r.y = (szY - r.height) / 2 + 2;

    _ntTuiDrawFrameDouble(r, gray, NULL);

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

    _ntTuiDrawProgressBar(p, r, blue, RED);

    if (__state.buffers[3] != NULL) _ntTuiDrawTextCentered(__state.buffers[3], 0xFF, r.y - 2, gray);
}