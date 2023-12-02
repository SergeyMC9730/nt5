#pragma once

#include <stddef.h>
#include <stdbool.h>

#include <raylib.h>

// update input box
void _ntUpdateInput(char *buffer, size_t max_input_length);

// update input pointer
void _ntUpdateInputPointer();

// draw input box
void _ntTuiDrawInput(char *buffer, size_t max_input_length, Vector2 position, Color text_color, Color background_color);