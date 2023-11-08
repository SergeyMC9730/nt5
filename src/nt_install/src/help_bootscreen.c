#include <nt5emul/boot_install.h>
#include <nt5emul/renderer.h>

#include <stdlib.h>

#include <string.h>

#include <stdio.h>

#include <signal.h>
#include <unistd.h>

extern char *__boot_install_strings[64];
extern ntinstall_t __state;

extern void _biAlarm1(int signum);

void _boot_install_update_step1() {
    // SetWindowSize(640, 400);

    int codepointCount = 0;
    int *codepoints = LoadCodepoints(__boot_install_strings[0], &codepointCount);

    __state.font = LoadFontEx("ntresources/Px437_IBM_VGA_8x16.ttf", 16, codepoints, codepointCount);

    __state.base_size = (Vector2){8, 16};

    free(codepoints);

    struct sigaction act;

    act.sa_handler = &_biAlarm1;
    act.sa_flags = SA_RESTART;

    sigaction(SIGALRM, &act, NULL);
    
    alarm(5);

    _biAlarm1(SIGALRM);

    _renderer_state.layers[0].update = NULL;

    #if BOOT_INSTALL_SKIP_STEP1 == 1
    _boot_install_beginstep2();
    alarm(0);
    #endif
}

void _boot_install_draw_step1() {   
    _biDrawBackground(__boot_install_strings[1], __state.buffers[1]);
}
