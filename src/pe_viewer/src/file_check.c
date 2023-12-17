/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  SergeyMC9730

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

    Contact SergeyMC9730 -- @dogotrigger in Discord
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
    printf("valid: %d\n", _ntPVFileCheck(file_path));
}