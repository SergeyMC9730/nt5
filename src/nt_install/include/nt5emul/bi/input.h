#pragma once

#include <stddef.h>
#include <stdbool.h>

#include <raylib.h>

typedef struct bi_input_t
{
    char *buffer;

    size_t max_input_length;
    
    Vector2 position;
} bi_input_t;


void _biUpdateInput(char *buffer, size_t max_input_length);
void _biUpdatePointer();
void _biDrawInput(char *buffer, size_t max_input_length, Vector2 position, Color col, Color bg);