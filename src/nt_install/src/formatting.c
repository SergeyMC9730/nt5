#include <nt5emul/bi/frame.h>
#include <nt5emul/bi/rectangle.h>
#include <nt5emul/bi/text.h>
#include <nt5emul/bi/input.h>

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

extern ntinstall_t __state;
extern char *__boot_install_strings[64];

void _boot_install_update_step7() {
    static char *files[] = {
        "123", "456", "789"
    };
}

void _boot_install_draw_step7() {
    _biDrawBackground(__boot_install_strings[7], __boot_install_strings[34]);
}