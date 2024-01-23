#include <nt5emul/modules/explorer/state.h>
#include <nt5emul/modules/explorer/explorer_command.h>

void init(cterm_t *info) {
    _state.runtime = info;
    
    info->register_command("explorer", "Run Explorer", true, explorer_command);

    return;
}

SET_INFORMATION("explorer", "XP Explorer", "1.0")