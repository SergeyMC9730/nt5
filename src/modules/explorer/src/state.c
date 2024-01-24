#include <nt5emul/modules/explorer/state.h>
#include <nt5emul/dwm/context.h>
#include <nt5emul/language_pack.h>

struct module_state _state = {0};

const char *get_string(const char *i, const char *l) {
    int lang_offset = 1;

    if (!strcmp(l, "ru")) {
        lang_offset = 2;
    }

    struct language_pack_cell cell = _ntFindInLanguagePack(i, _ntDwmGetGlobal()->lpack);
    
    const char **ptr = &cell;

    const char *string = ptr[lang_offset];

    return string;
}