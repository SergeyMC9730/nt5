
#include <nt5emul/modules/notepad/state.h>
#include <nt5emul/modules/notepad/notepad_command.h>


void init(cterm_t *info) {
    _state.runtime = info;

    info->register_command("notepad", "Codegenned notepad command", false, notepad_command);


    return;
}

SET_INFORMATION("notepad", "Codegenned project", "1.00")
