/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  Sergei Baigerov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact Sergei Baigerov -- @dogotrigger in Discord
*/

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
    bool valid = _ntPVFileCheck(file_path);
    
    printf("valid: %d\n", valid);

    if (valid) _ntPVLoadPe(file_path);
}

#include <nt5emul/pv/state.h>

void _ntPVLoadPe(const char *file_path) {
    if (!_ntPVFileCheck(file_path)) return;

    __state.file_path = file_path;

    pe_ctx_t ctx;

    pe_load_file(&ctx, file_path);
    pe_parse(&ctx);

    __state.sections = ctx.pe.num_sections;
    __state.directories = ctx.pe.num_directories;

    __state.file = ctx;

    __state.current_page_name = "PE FILE INFO";
}