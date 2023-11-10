#include <nt5emul/bi/frame.h>
#include <nt5emul/bi/rectangle.h>
#include <nt5emul/bi/text.h>
#include <nt5emul/bi/input.h>

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

extern ntinstall_t __state;
extern char *__boot_install_strings[64];

void _boot_install_update_step6() {
    static char *files[] = {
        "123", "456", "789"
    };

    _biUpdateInput(__state.buffers[3], 32);
}

void _boot_install_draw_step6() {
    _biDrawBackground(__boot_install_strings[7], "");

    _biDrawInput(__state.buffers[3], 32, (Vector2){20, 20}, BLACK, WHITE);
}