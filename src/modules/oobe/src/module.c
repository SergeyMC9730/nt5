#include <nt5emul/modules/oobe/state.h>
#include <nt5emul/modules/oobe/msoobe_command.h>

void init(cterm_t *info) {
    _state.runtime = info;
    
    info->register_command("msoobe", "Run Out of Box Experience recreation", false, msoobe_command);

    return;
}

SET_INFORMATION("oobe", "Out of Box Experience", "1.00")