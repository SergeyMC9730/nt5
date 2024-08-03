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

#include <nt5emul/modules/logonui/state.h>
#include <cterm/cterm.h>
#include <nt5emul/modules/logonui/logonui_command.h>

void on_init(struct cterm_module *info) {
    _ctermRegisterCommand(info->cterm_instance, "logonui", "Logon UI", logonui_command);

    return;
}

CTERM_INIT_MODULE("logonui", "Logon UI", "2.0.0")