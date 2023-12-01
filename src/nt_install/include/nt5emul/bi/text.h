#pragma once

#include <raylib.h>

// draw text
void _biTextDraw(const char *str, unsigned char x, unsigned char y, Color col);

/*
    draw text centered
    
    if X equals to 0xFF then text would be centered by X;
    if Y equals to 0xFF then text would be centered by Y.

    in other cases x and y are gonna be position offsets.
*/
void _biTextDrawCentered(const char *str, signed char x, signed char y, Color col);