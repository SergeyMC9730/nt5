#pragma once

#include <raylib.h>

#include <nt5emul/bi/menu.h>

typedef struct ntinstall_t {
    Font font;
    Vector2 base_size;

    char *buffers[16];

    unsigned char idx0;

    bi_menu_t menu0;

    bool show_input_pointer;
} ntinstall_t;