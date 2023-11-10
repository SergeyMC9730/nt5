#include <nt5emul/bi/input.h>
#include <nt5emul/bi/text.h>
#include <nt5emul/bi/rectangle.h>

#include <raylib.h>

#include <string.h>

void _biUpdateInput(char *buffer, size_t max_input_length) {
    size_t current_length = strlen(buffer);

    int key = GetCharPressed();

    // printf("%d %c\n", key, (char)key);

    while (key > 0) {
        if (((current_length) < max_input_length)) {
            buffer[current_length++] = (char)key;
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        buffer[--current_length] = 0;
    }
}
void _biDrawInput(char *buffer, size_t max_input_length, Vector2 position, Color col, Color bg) {
    _biRectangleDraw((Rectangle){position.x, position.y, max_input_length, 1}, bg);

    size_t left = max_input_length;

    for (size_t i = 0; i < max_input_length; i++) {
        char data[2] = {*(buffer + i), 0};

        if (data[0] == 0) break;

        _biTextDraw((const char *)data, position.x + i, position.y, col);
        left--;
    }

    if (left != 0) {
        size_t l = strlen(buffer);
        _biTextDraw("_", position.x + l, position.y, col);
    }
}