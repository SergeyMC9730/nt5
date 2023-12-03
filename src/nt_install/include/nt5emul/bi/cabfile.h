#pragma once

#include <stddef.h>

#include "../../../arrays/include/nt5emul/arrays/rsb_array_gen.h"

struct cabfile_file {
    const char *internal_name;
    const char *destination_path;
};

RSB_ARRAY_DEF_GEN(struct cabfile_file, cabfile_file_array);

struct cabfile {
    const char *cabinet_path;
    rsb_array_cabfile_file_array *files;
};

RSB_ARRAY_DEF_GEN(struct cabfile, cabfile);