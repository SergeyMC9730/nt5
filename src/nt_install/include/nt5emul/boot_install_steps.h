#pragma once

#include <nt5emul/bi/menu.h>

void _boot_install_beginstep1(); // loading data
void _boot_install_beginstep2(); // welcome screen
void _boot_install_beginstep3(); // reading license agreement
void _boot_install_beginstep4(); // partition manager
void _boot_install_beginstep5(int idx, bi_menu_t *menu); // partition formatting
void _boot_install_beginstep6(int idx, bi_menu_t *menu); // xp installation files path selecting
void _boot_install_beginstep7(); // formatting