#pragma once

#include <raylib.h>

struct nt_tui_environment {
    Font font;

    // size in characters
    Vector2 base_font_size;

    bool show_input_pointer;
};

// load text ui environment
void _ntTuiLoadEnvironment(const char *font_path, Vector2 base_font_size);

// load text ui environment with default parameters
void _ntTuiLoadEnvironmentDefault();