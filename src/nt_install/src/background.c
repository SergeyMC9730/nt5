#include <nt5emul/boot_install.h>

#include <string.h>
#include <stdio.h>

#include <nt5emul/bi/text.h>
#include <nt5emul/bi/rectangle.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

void _biDrawBackgroundEx(const char *product_name, const char *help_shortcuts, Color bg_color, Color status_color, Color status_text_color) {    
    int window_size_x = GetRenderWidth() / __state.base_size.x; // get x size in characters
    int window_size_y = GetRenderHeight() / __state.base_size.y; // get y size in characters
    
    // clear background
    ClearBackground(bg_color);
    
    int l = -3; // product name length

    // check if product name exists and do processing of it
    if (product_name != NULL) {
        _biTextDraw(product_name, 0, 1, status_color);

        // get length of product name
        l = strlen(product_name) + 1;

        // draw line below product name
        for (unsigned int i = 0; i < l; i++) {
            // ═
            _biTextDraw(__boot_install_strings[2], i, 2, status_color);
        }
    }

    // format fps string
    snprintf(__state.buffers[0], 32, __boot_install_strings[3], (1.f / GetFrameTime()));

    /*
        draw fps

        if product name doesn't exist we can 
        just  set  its  length  to -3  and X 
        position  for  fps label  would be 0
    */
    _biTextDraw(__state.buffers[0], l + 3, 2, GRAY);

    // check if help shortcuts exists and do processing of it
    if (help_shortcuts != NULL) {
        // draw status background
        _biRectangleDraw((Rectangle){0, 29, 85, 1}, status_color);

        // draw help shortcuts
        _biTextDraw(help_shortcuts, 2, 29, status_text_color);
    }
}

void _biDrawBackground(const char *product_name, const char *help_shortcuts) {

    return _biDrawBackgroundEx(
        product_name,
        help_shortcuts, 
        (Color){0x00, 0x09, 0xAB, 0xFF}, // blue background
        (Color){0xA8, 0xA8, 0xA8, 0xFF}, // gray status bar
        BLACK
    );
}