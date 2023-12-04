#include <nt5emul/renderer.h>

#include <nt5emul/tui/environment.h>

#include <nt5emul/tui/text.h>
#include <nt5emul/tui/menu.h>
#include <nt5emul/tui/rectangle.h>
#include <nt5emul/tui/frame.h>

#include <nt5emul/tui/file_selector.h>

struct nt_file_selector_menu *menu0;

#include <dirent.h> 
#include <stdio.h> 
#include <string.h>

void update1() {
    int c = GetRenderHeight() / 16 - 7;

    if (menu0->items_per_page != c) {
        menu0->items_per_page = c;
        _ntFileSelectorSetListing(menu0);
    }        

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

    renderer_state_t *st = _ntRendererGetState();

    Rectangle r;

    r.x = 0;
    r.y = 0;
    r.width = GetRenderWidth() / 8 + 1;
    r.height = GetRenderHeight() / 16 + 1;

    _ntTuiDrawRectangleGr(r, BLACK, gray);
    _ntTuiDrawTextCentered("SELECT PE FILE", 0xFF, 1, WHITE);

    r.x = 2;
    r.y = 2;
    r.width = GetRenderWidth() / 8 - 6;
    r.height = GetRenderHeight() / 16 - 4;

    _ntTuiDrawFrame(r, WHITE, NULL);

    // _ntTuiDrawTextCentered("hello", 0xFF, 10, WHITE);

    _ntTuiDrawMenu(menu0->base);

    const char *s1 = "GREEN";
    const char *s2 = "file - possible PE file";

    size_t x = r.x;
    size_t y = r.y + r.height + 1;

    _ntTuiDrawText(s1, x, y, GREEN);
    x += strlen(s1) + 1;

    _ntTuiDrawText(s2, x, y, WHITE);

    DrawFPS(8, 16);
}

int main() {
    // init NT renderer
	_ntRendererCreateEnvironment();

    int sx = 640;
    int sy = 480;

    SetWindowSize(sx, sy);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(sx, sy);

    renderer_state_t *st = _ntRendererGetState();

    st->layers[0].draw = draw;
    st->layers[0].update = update;

    int c = sy / 16 - 7;

    menu0 = _ntLoadFileSelector("./", c);

    RSBAddElementString(menu0->wanted_fileformats, ".exe");
    RSBAddElementString(menu0->wanted_fileformats, ".dll");

    _ntFileSelectorSetListing(menu0);

    menu0->base.x = 4;
    menu0->base.y = 3;

    _ntRendererJoin();
}