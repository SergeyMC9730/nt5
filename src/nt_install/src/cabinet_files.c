#include <nt5emul/nt_install.h>

// expose internal values

#include <string.h>

extern ntinstall_t __state; // installation state

#include <stdio.h>

RSB_ARRAY_IMPL_GEN(struct cabfile_file, cabfile_file_array);
RSB_ARRAY_IMPL_GEN(struct cabfile, cabfile);

// void _boot_install_cab_put_file(size_t index, const char *internal_name, const char *destination_path) {
//     for (size_t i = 0; i < __state.cabfile_array_size; i++) {
//         struct cabfile_file *file = &__state.cabfile_list[index].files[i];

//         if (!file->destination_path || !file->internal_name) {
//             file->destination_path = destination_path;
//             file->internal_name = internal_name;

//             printf("added file \"%s\" into %d\n", internal_name, index);
//         }
//     }
// }

struct cabfile *_boot_install_cab_putcabinet(const char *path) {
    struct cabfile cab;

    cab.cabinet_path = path;
    cab.files = RSBCreateArraycabfile_file_array();

    RSBAddElementcabfile(__state.cabfile_list, cab);

    struct cabfile *res = &__state.cabfile_list->objects[__state.cabfile_list->current_index - 1];

    return res;
}

extern const char *_bi_cabinet_listing[567];

void _boot_install_create_cab_files() {
    __state.cabfile_list = RSBCreateArraycabfile();

    size_t l = sizeof(_bi_cabinet_listing) / sizeof(const char *);

    size_t i = 0;

    struct cabfile *current_cab;

    const char *dest = NULL;
    const char *file = NULL;

    while (i < l) {
        const char *f = _bi_cabinet_listing[i];

        if (f == NULL) {
            current_cab = NULL;
            continue;
        }

        size_t file_length = strlen(f);

        if (f[file_length - 1] == '_') {
            // it is a cabinet file

            current_cab = _boot_install_cab_putcabinet(f);
        } else if (f[0] == '*') {
            // it is a destination path

            f++;
            dest = f;
        } else {
            // it is a filename inside of cabinet archive

            file = f;

            struct cabfile_file cfile;
            cfile.destination_path = dest;
            cfile.internal_name = file;

            RSBAddElementcabfile_file_array(current_cab->files, cfile);

            // printf("added file %s (%s) to cabinet %s\n", file, dest, current_cab->cabinet_path);
        }

        i++;
    }
}