#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

// expose timer
extern void _boot_install_timer(void(*callback)(), float seconds);

// expose internal values

extern ntinstall_t __state; // installation state

void _boot_install_throw_error_end() {
    __state.status_bar_is_error = false;
}

void _boot_install_throw_error(const char *error) {
    if (__state.status_bar_is_error) return;
    
    __state.status_bar_is_error = true;
    __state.status_bar_error = error;

    _boot_install_timer(_boot_install_throw_error_end, 0.5f);
}