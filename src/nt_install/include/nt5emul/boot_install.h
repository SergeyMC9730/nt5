#pragma once

#include <raylib.h>

#define BOOT_INSTALL_SKIP_STEP1 1

#include <nt5emul/bi/menu.h>

typedef struct ntinstall_t {
    Font font;
    Vector2 base_size;

    char *buffers[16];

    unsigned char idx0;

    bi_menu_t menu0;
} ntinstall_t;

void _boot_install_begin();

void _boot_install_beginstep1(); // loading data
void _boot_install_beginstep2(); // welcome screen
void _boot_install_beginstep3(); // reading license agreement
void _boot_install_beginstep4(); // partition manager
void _boot_install_beginstep5(int idx, bi_menu_t *menu); // partition formatting
void _boot_install_beginstep6(int idx, bi_menu_t *menu); // formatting progress

void _biDrawBackground(const char *product_name, const char *help_shortcuts);