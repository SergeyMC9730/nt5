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

#include <nt5emul/modules/explorer/state.h>
#include <nt5emul/language_pack.h>
#include <nt5emul/nt_config.h>
#include <nt5emul/dwm/context.h>

void load_text() {
    struct nt_config cfg = _ntGetConfig("nt/config.json");
    struct dwm_context *ctx = _ntDwmGetGlobal();

    const char *lang = cfg.selected_lang;

    // free config
    _ntUnloadConfig(cfg);

    _state.cterm_explorer_title = _ntGetStringInLanguagePack(ctx->lpack, "cterm_explorer_title", lang);
    _state.cterm_shell_start_classic = _ntGetStringInLanguagePack(ctx->lpack, "cterm_shell_start_classic", lang);
    _state.cterm_shell_intro_text = _ntGetStringInLanguagePack(ctx->lpack, "cterm_shell_intro_text", lang);
    _state.cterm_explorer_system_tasks = _ntGetStringInLanguagePack(ctx->lpack, "cterm_explorer_system_tasks", lang);
    _state.cterm_explorer_other_places = _ntGetStringInLanguagePack(ctx->lpack, "cterm_explorer_other_places", lang);
    _state.cterm_explorer_st_vsi = _ntGetStringInLanguagePack(ctx->lpack, "cterm_explorer_st_vsi", lang);
    _state.cterm_explorer_st_arp = _ntGetStringInLanguagePack(ctx->lpack, "cterm_explorer_st_arp", lang);
    _state.cterm_explorer_st_cs = _ntGetStringInLanguagePack(ctx->lpack, "cterm_explorer_st_cs", lang);
    _state.cterm_explorer_op_nmp = _ntGetStringInLanguagePack(ctx->lpack, "cterm_explorer_op_nmp", lang);
    _state.cterm_explorer_op_md = _ntGetStringInLanguagePack(ctx->lpack, "cterm_explorer_op_md", lang);
    _state.cterm_explorer_op_sd = _ntGetStringInLanguagePack(ctx->lpack, "cterm_explorer_op_sd", lang);
    _state.cterm_explorer_op_cp = _ntGetStringInLanguagePack(ctx->lpack, "cterm_explorer_op_cp", lang);
    _state.cterm_shell_intro_title = _ntGetStringInLanguagePack(ctx->lpack, "cterm_shell_intro_title", lang);
}