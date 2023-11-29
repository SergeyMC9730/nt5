#pragma once

#include <stddef.h>
#include <stdbool.h>

#include <raylib.h>

// input structure
typedef struct bi_input_t
{
    char *buffer; // input buffer

    size_t max_input_length; // how much characters you can put there
    
    Vector2 position; // box position
} bi_input_t;

// update input box
void _biUpdateInput(char *buffer, size_t max_input_length);

// update input pointer
void _biUpdateInputPointer();

// draw input box
void _biDrawInput(char *buffer, size_t max_input_length, Vector2 position, Color text_color, Color background_color);