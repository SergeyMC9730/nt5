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

#include <nt5emul/tui/environment.h>
#include <nt5emul/timer.h>

extern struct nt_tui_environment _ntTuiEnvironment;

// required for codepoints to load
// this giant string is going to be concatenated on compile time

const char *_ntTuiCodepoints =  "QWERTYUIOPASDFGHJKLZXCVBNM" // english alphabet with all upper case characters
                                "qwertyuiopasdfghjklzxcvbnmzxcvbnm" // english alphabet with all lower case characters
                                "[]{}()" // brackets
                                "ЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ" // cyrillic alphabet with all upper case characters
                                "ёйцукенгшщзхъфывапролджэячсмитьбю" // cyrillic alphabet with all lower case chararcters
                                ",.;!?:" // punctuation      
                                "/\\|" // slashes
                                "1234567890" // numbers
                                "<>-=+~*^%№" // math signs
                                "\"'`" // quotation marks
                                "@#$&_" // random characters 
                                "═ • │ ┤ ╡ ╢ ╖ ╕ ╣ ║ ╗ ╝ ╜ ╛ ┐ └ ┴ ┬ ├ ─ ┼ ╞ ╟ ╚ ╔ ╩ ╦ ╠ ═ ╬ ╧ ╨ ╤ ╥ ╙ ╘ ╒ ╓ ╫ ╪ ┘ ┌ █ ▄ ▌ ▐ ▀ "; // lines

extern void _ntUpdatePointer();

#include <stdlib.h>

// load text ui environment
void _ntTuiLoadEnvironment(const char *font_path, Vector2 base_font_size) {
    // load codepoints
    int codepointCount = 0;
    int *codepoints = LoadCodepoints(_ntTuiCodepoints, &codepointCount);

    // load font with them
    _ntTuiEnvironment.font = LoadFontEx(font_path, 16, codepoints, codepointCount);
    // set base font size
    _ntTuiEnvironment.base_font_size = base_font_size;
    // free allocation done by LoadCodepoints
    free(codepoints);

    _ntInstallTimer(_ntUpdatePointer, 0.5f, NULL);
}

void _ntTuiLoadEnvironmentDefault() {
    return _ntTuiLoadEnvironment("ntresources/Px437_IBM_VGA_8x16.ttf", (Vector2){8, 16});
}