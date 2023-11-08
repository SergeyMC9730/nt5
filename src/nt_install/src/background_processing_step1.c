#include <nt5emul/boot_install.h>

#include <nt5emul/renderer.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char *__boot_install_strings[64];
extern ntinstall_t __state;

extern void _boot_install_update_step2();
extern void _boot_install_draw_step2();

void _biAlarm1(int signum) {
    int lines = 3;

    if (signum == SIGALRM) {
        __state.buffers[1] = __boot_install_strings[4 + (__state.idx0 % lines)];

        __state.idx0++;

        if (__state.idx0 >= (lines + 1)) {
            _boot_install_beginstep2();
        } else {
            alarm(5);
        }
    } else {
        exit(-1);
    }
}