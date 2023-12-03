#include <libpe/pe.h>

void _boot_try_parse_explorer() {
    printf("\n");

    pe_ctx_t ctx;

    pe_err_e err = pe_load_file(&ctx, "nt/binary/explorer.exe");

    if (err != LIBPE_E_OK) {
        printf("libpe error (read):\n");
        pe_error_print(stdout, err);
        
        return;
    }

    err = pe_parse(&ctx);
    if (err != LIBPE_E_OK) {
        printf("libpe error (read):\n");
        pe_error_print(stdout, err);
        
        return;
    }

    if (!pe_is_pe(&ctx)) {
        printf("file is not pe\n");
        
        return;
    }

    printf("entrypoint: %#lx\n\n", ctx.pe.entrypoint);
    
    int i = 0;

    IMAGE_DATA_DIRECTORY *dir = ctx.pe.directories[i];

    printf(":: DIRECTORIES (%d) ::\n", ctx.pe.num_directories);
    while (i < ctx.pe.num_directories) {
        dir = ctx.pe.directories[i];

        printf("i=%d; size=%d; vaddr=0x%02X\n", i, dir->Size, dir->VirtualAddress);
        
        i++;
    }

    i = 0;

    // pe_resources_t *r = pe_resources(&ctx);

    // pe_resource_debug_nodes(&ctx, r->root_node);

}