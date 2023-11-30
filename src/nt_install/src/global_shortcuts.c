#include <nt5emul/renderer.h>
#include <nt5emul/bi/ntcore.h>
#include <nt5emul/boot_install_settings.h>

#include <raylib.h>

#include <stdio.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings

void _boot_install_shortcuts_update() {
    if (IsKeyPressed(KEY_F9)) {
        puts(__boot_install_strings[37]); // F9 Info:

        const char *s_busy = __boot_install_strings[39]; // busy
        const char *s_free = __boot_install_strings[40]; // free

        for (size_t i = 0; i < NT_CORES; i++) {
            // check if core is busy or not
            bool busy = _biCoreBusy(i);
            
            //  * C%zu - %s
            printf(__boot_install_strings[38], i, busy ? s_busy : s_free);
        }
    }
}