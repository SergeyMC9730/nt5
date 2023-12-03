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

    _ntInstallTimer(_ntUpdatePointer, 0.5f);
}

void _ntTuiLoadEnvironmentDefault() {
    return _ntTuiLoadEnvironment("ntresources/Px437_IBM_VGA_8x16.ttf", (Vector2){8, 16});
}