#include <nt5emul/renderer.h>

#include <nt5emul/tui/environment.h>

#include <nt5emul/tui/text.h>
#include <nt5emul/tui/menu.h>

#include <nt5emul/tui/file_selector.h>

struct nt_file_selector_menu *menu0;

#include <dirent.h> 
#include <stdio.h> 
#include <string.h>

void update1() {
    _ntUpdateFileSelector(menu0);
}

void update() {
    renderer_state_t *st = _ntRendererGetState();

    // init text ui environment
    _ntTuiLoadEnvironmentDefault();

    st->layers[0].update = update1;
}

void draw() {
    Color gray = (Color){ 30, 30, 30, 255 };

    ClearBackground(gray);

    // _ntTuiDrawTextCentered("hello", 0xFF, 10, WHITE);

    _ntTuiDrawMenu(menu0->base);
}

int main() {
    // init NT renderer
	_ntRendererCreateEnvironment();

    renderer_state_t *st = _ntRendererGetState();

    st->layers[0].draw = draw;
    st->layers[0].update = update;

    menu0 = _ntLoadFileSelector("./", 15);

    menu0->base.x = 10;
    menu0->base.y = 10;

    _ntRendererJoin();
}