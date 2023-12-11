#pragma once

#include <nt5emul/tui/file_selector.h>

struct pe_viewer_state {
    struct nt_file_selector_menu *file_selector;
};

extern struct pe_viewer_state __state;