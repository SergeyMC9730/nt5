/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  SergeyMC9730

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact SergeyMC9730 -- @dogotrigger in Discord
*/

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