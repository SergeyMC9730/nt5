#pragma once

#include <raylib.h>

// draw frame with default character mapping
// `description` can be NULL, in this case text would not be displayed
void _biDrawFrame(Rectangle r, Color col, const char *description);

// draw frame with double lines
// `description` can be NULL, In this case text would be displayed
void _biDrawFrameDouble(Rectangle r, Color col, const char *description);

// draw frame with custom character mapping
// `mapping` contains an array with 7 strings. each one contains frame element.
// see `mapping` example in `interface_frame.c:61`
// `description` can be NULL, in this case text would not be displayed
void _biDrawFrameEx(Rectangle r, Color col, const char **mapping, const char *description);