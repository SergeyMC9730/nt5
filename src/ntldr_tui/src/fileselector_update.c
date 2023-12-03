#include <nt5emul/tui/file_selector.h>

void _ntUpdateFileSelector(struct nt_file_selector_menu *menu) {
    _ntUpdateMenu(&menu->base);
}