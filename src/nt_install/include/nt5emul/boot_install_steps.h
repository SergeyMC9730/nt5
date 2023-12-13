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