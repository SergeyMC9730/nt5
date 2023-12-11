#include <nt5emul/pv/file_check.h>

#include <libpe/pe.h>

bool _ntPVFileCheck(const char *file_path) {
    pe_ctx_t ctx;

    pe_err_e err = pe_load_file(&ctx, file_path);

    if (err != LIBPE_E_OK) goto invalid;

    err = pe_parse(&ctx);
    if (err != LIBPE_E_OK) goto invalid;

    if (!pe_is_pe(&ctx)) goto invalid;

    pe_unload(&ctx); 
    return true;

    invalid:
    pe_unload(&ctx); 
    return false;
}

void _ntPVOnFileClick(struct nt_file_selector_menu *menu, const char *file_path) {
    printf("valid: %d\n", _ntPVFileCheck(file_path));
}