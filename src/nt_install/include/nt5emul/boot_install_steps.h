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
#pragma once

#include <nt5emul/tui/menu.h>

void _boot_install_beginstep1(); // loading data
void _boot_install_beginstep2(); // welcome screen
void _boot_install_beginstep3(); // reading license agreement
void _boot_install_beginstep4(); // partition manager
void _boot_install_beginstep5(int idx, struct nt_tui_menu *menu); // partition formatting
void _boot_install_beginstep6(int idx, struct nt_tui_menu *menu); // xp installation files path selecting
void _boot_install_beginstep7(); // formatting
void _boot_install_beginstep8(); // copying files
void _boot_install_beginstep9(); // setting up environment
void _boot_install_beginstep10(); // restarting pc