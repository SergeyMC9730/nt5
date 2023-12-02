#include <nt5emul/tui/input.h>
#include <nt5emul/tui/text.h>
#include <nt5emul/tui/rectangle.h>

#include <nt5emul/timer.h>

#include <raylib.h>

#include <string.h>

#include <nt5emul/tui/environment.h>

extern struct nt_tui_environment _ntTuiEnvironment;

void _ntInstallTimer(void(*callback)(), float seconds);

void _ntUpdateInput(char *buffer, size_t max_input_length) {
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
void _ntTuiDrawInput(char *buffer, size_t max_input_length, Vector2 position, Color col, Color bg) {
    _ntTuiDrawRectangle((Rectangle){position.x, position.y, max_input_length, 1}, bg);

    size_t left = max_input_length;

    for (size_t i = 0; i < max_input_length; i++) {
        char data[2] = {*(buffer + i), 0};

        if (data[0] == 0) break;

        _ntTuiDrawText((const char *)data, position.x + i, position.y, col);
        left--;
    }

    if ((left != 0) && _ntTuiEnvironment.show_input_pointer) {
        size_t l = strlen(buffer);
        _ntTuiDrawText("_", position.x + l, position.y, col);
    }
}

void _ntUpdatePointer() {
    _ntTuiEnvironment.show_input_pointer = !_ntTuiEnvironment.show_input_pointer;

    _ntInstallTimer(_ntUpdatePointer, 0.5f);
}