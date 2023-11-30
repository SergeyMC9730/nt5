#pragma once

#include <raylib.h>

// draw nt install background with standard colors
void _biDrawBackground(const char *product_name, const char *help_shortcuts);

// draw nt install background with custom colors
void _biDrawBackgroundEx(
    const char *product_name,
    const char *help_shortcuts,

    Color background_color,
    Color status_color,
    Color status_text_color
);

// background layer functions
void _boot_install_backgroundInit();
void _boot_install_drawBackground();