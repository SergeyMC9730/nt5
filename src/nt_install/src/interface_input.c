#include <nt5emul/bi/input.h>
#include <nt5emul/bi/text.h>
#include <nt5emul/bi/rectangle.h>

#include <raylib.h>

#include <string.h>

#include <nt5emul/boot_install.h>

void _ntInstallTimer(void(*callback)(), float seconds);

// expose internal values

extern ntinstall_t __state; // installation state

void _biUpdateInput(char *buffer, size_t max_input_length) {
    size_t current_length = strlen(buffer);

    // get pressed character
    int key = GetCharPressed();

    // do it in a loop because 
    // pressed key might be an 
    // unicode character
    while (key > 0) {
        // check if current length is smaller 
        // than    maximum    input    length
        // also  check for  array  boundaries
        if (((current_length) < (max_input_length - 1))) {
            // put char
            buffer[current_length++] = (char)key;
        }

        // get pressed char again
        key = GetCharPressed();
    }

    // array boundaries check
    if (current_length == 0) return;
    
    // remove one char
    if (IsKeyPressedRepeat(KEY_BACKSPACE) || IsKeyPressed(KEY_BACKSPACE)) {
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

    if ((left != 0) && __state.show_input_pointer) {
        size_t l = strlen(buffer);
        _biTextDraw("_", position.x + l, position.y, col);
    }
}

void _biUpdatePointer() {
    __state.show_input_pointer = !__state.show_input_pointer;

    _ntInstallTimer(_biUpdatePointer, 0.5f);
}