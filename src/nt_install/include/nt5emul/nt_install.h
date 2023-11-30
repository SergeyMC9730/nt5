#pragma once

#include <raylib.h>

#include <nt5emul/bi/menu.h>

typedef struct ntinstall_t {
    Font font;
    Vector2 base_size;

    char *buffers[16];

    // menu related variables
    unsigned char idx0;
    bi_menu_t menu0;

    bool show_input_pointer;

    unsigned char selected_format_option;

    bool status_bar_is_error;
    const char *status_bar_error;

    const char *product_name_label;
    const char *status_bar_label;

    float timer0;
} ntinstall_t;