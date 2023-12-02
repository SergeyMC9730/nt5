#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>
#include <nt5emul/timer.h>

// expose internal values

extern ntinstall_t __state; // installation state

void _boot_install_throw_error_end() {
    __state.status_bar_is_error = false;
}

void _boot_install_throw_error(const char *error) {
    if (__state.status_bar_is_error) return;
    
    __state.status_bar_is_error = true;
    __state.status_bar_error = error;

    _ntInstallTimer(_boot_install_throw_error_end, 0.5f);
}