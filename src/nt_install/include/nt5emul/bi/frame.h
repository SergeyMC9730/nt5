#pragma once

#include <raylib.h>

// draw frame with default character mapping
void _biDrawFrame(Rectangle r, Color col);

// draw frame with custom character mapping
void _biDrawFrameEx(Rectangle r, Color col, const char **mapping);