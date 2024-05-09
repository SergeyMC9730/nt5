/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  Sergei Baigerov

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

    Contact Sergei Baigerov -- @dogotrigger in Discord
*/

#include <raylib.h>

const char *_ntDwmTranslateKeyToStr(int key) {
    const char *symtable[] = {
        "A", "B", "C", "D", "E", "F",
        "G", "H", "I", "J", "K", "L",
        "M", "N", "O", "P", "Q", "R",
        "S", "T", "U", "V", "W", "X",
        "Y", "Z"
    };

    switch(key) {
        case KEY_LEFT_CONTROL: {
            return "LCtrl";
        }
        case KEY_RIGHT_CONTROL: {
            return "RCtrl";
        }
        case KEY_LEFT_SHIFT: {
            return "LShift";
        }
        case KEY_RIGHT_SHIFT: {
            return "RShift";
        }
        case KEY_RIGHT_ALT: {
            return "RAlt";
        }
        case KEY_LEFT_ALT: {
            return "LAlt";
        }
        case KEY_A: case KEY_B: case KEY_C:
        case KEY_D: case KEY_E: case KEY_F:
        case KEY_G: case KEY_H: case KEY_I:
        case KEY_J: case KEY_K: case KEY_L:
        case KEY_M: case KEY_N: case KEY_O:
        case KEY_P: case KEY_Q: case KEY_R:
        case KEY_S: case KEY_T: case KEY_U:
        case KEY_V: case KEY_W: case KEY_X:
        case KEY_Y: case KEY_Z: {
            return symtable[key - KEY_A];
        }
        default: {
            return "";
        }
    }
}