#pragma once

#include <raylib.h>

#define BOOT_INSTALL_SKIP_STEP1 1

typedef struct ntinstall_t {
    Font font;
    Vector2 base_size;

    char *buffers[16];

    unsigned char idx0;
} ntinstall_t;

void _boot_install_begin();

void _boot_install_beginstep1(); // loading data
void _boot_install_beginstep2(); // welcome screen
void _boot_install_beginstep3(); // reading license agreement

void _biTextDraw(const char *str, unsigned char x, unsigned char y, Color col);
void _biRectangleDraw(Rectangle r, Color col);

void _biDrawBackground(const char *product_name, const char *help_shortcuts);