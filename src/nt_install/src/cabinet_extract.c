#include <nt5emul/boot_install.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <archive.h>

#include <archive_entry.h>

#include <stdlib.h>

// expose internal values

extern ntinstall_t __state; // installation state

static int copy_data(struct archive *ar, struct archive *aw) {
    int r;
    const void *buff;
    size_t size;
    la_int64_t offset;

    for (;;) {
        r = archive_read_data_block(ar, &buff, &size, &offset);

        if (r == ARCHIVE_EOF) return (ARCHIVE_OK);
        if (r < ARCHIVE_OK) return (r);

        r = archive_write_data_block(aw, buff, size, offset);
        
        if (r < ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(aw));
            return (r);
        }
    }
}

void _boot_install_extract_cabinet(const char *cab, const char *path) {
    if (!cab) return;

    // check if the cabinet exists
    size_t l = __state.cabfile_list->len;
    size_t i = 0;

    bool exists = false;

    struct cabfile c;

    while ((i < l) && !exists) {
        // get cabinet
        c = RSBGetAtIndexcabfile(__state.cabfile_list, i);
        
        // comparison
        exists = !strcmp(c.cabinet_path, cab);

        i++;
    }

    if (!exists) return;

    struct archive *a = archive_read_new();
    struct archive_entry *entry;

    int r = 0;

    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    r = archive_read_open_filename(a, path, 256);

    if (r != ARCHIVE_OK) {
        printf("r=%d; something is wrong (%d %s); exiting\n", r, archive_errno(a), archive_error_string(a));

        archive_read_close(a);

        return;
    }

    struct archive *a_disk = archive_write_disk_new();
    archive_write_disk_set_options(a_disk, ARCHIVE_EXTRACT_TIME);
    archive_write_disk_set_standard_lookup(a_disk);

    while (archive_read_next_header(a, &entry) != ARCHIVE_EOF) {
        const char *s = archive_entry_pathname(entry);

        __state.cabfile_current_file = __state.buffers[8];
        strcpy(__state.buffers[8], s);

        r = archive_write_header(a_disk, entry);

        // printf("extracting %s\n", s);

        if (r != ARCHIVE_OK) {
            printf("r=%d; something is wrong (%d %s); exiting\n", r, archive_errno(a), archive_error_string(a));

            archive_read_close(a);

            return;
        }

        if (archive_entry_size(entry) > 0) {
            r = copy_data(a, a_disk);

            if (r != ARCHIVE_OK) {
                printf("r=%d; something is wrong (%d %s); exiting\n", r, archive_errno(a), archive_error_string(a));

                archive_read_close(a);

                return;
            }
        }

        r = archive_write_finish_entry(a_disk);

        if (r != ARCHIVE_OK) {
            printf("r=%d; something is wrong (%d %s); exiting\n", r, archive_errno(a), archive_error_string(a));

            archive_read_close(a);

            return;
        }

        archive_read_data_skip(a);
    }

    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(a_disk);
    archive_write_free(a_disk);

    l = c.files->len;
    i = 0;

    while (i < l) {
        struct cabfile_file f = RSBGetAtIndexcabfile_file_array(c.files, i);

        char *buffer = (char *)MemAlloc(256);

        snprintf(buffer, 256, "cp %s %s", f.internal_name, f.destination_path);
        system(buffer);

        snprintf(buffer, 256, "rm %s", f.internal_name);
        system(buffer);

        i++;
    }

    return;
}