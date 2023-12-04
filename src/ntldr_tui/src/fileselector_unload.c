#include <nt5emul/tui/file_selector.h>
#include <stdlib.h>
#include <string.h>

void _ntUnloadFileSelector(struct nt_file_selector_menu *menu) {
    size_t l = menu->listing->len;

    for (size_t i = 0; i < l; i++) {
        free((char *)menu->listing->objects[i]);
    }

    RSBDestroyString(menu->listing);
    RSBDestroyString(menu->wanted_fileformats);
    RSBDestroyColor(menu->colors);

    free(menu);
    
    return;
}