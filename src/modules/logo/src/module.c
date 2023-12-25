#include <nt5emul/modules/logo/state.h>
#include <nt5emul/modules/logo/logo_command.h>

void init(cterm_t *info) {
    _state.runtime = info;
    
    info->register_command("logo", "Run XP logo animation", true, logo_command);

    // info->load_module("applications/libntmod_oobe.so", "init");

    return;
}

SET_INFORMATION("logo", "XP Logo", "1.10")