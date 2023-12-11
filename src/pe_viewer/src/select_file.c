#include <nt5emul/pv/select_file.h>
#include <nt5emul/pv/state.h>
#include <nt5emul/renderer.h>
#include <nt5emul/tui/text.h>
#include <nt5emul/tui/menu.h>
#include <nt5emul/tui/rectangle.h>
#include <nt5emul/tui/frame.h>
#include <nt5emul/tui/environment.h>
#include <nt5emul/pv/file_check.h>
#include <string.h>

void _ntPVSelectFileUpdate() {
    int c = GetRenderHeight() / 16 - 7;

    if (__state.file_selector->items_per_page != c) {
        __state.file_selector->items_per_page = c;
        _ntFileSelectorSetListing(__state.file_selector);
    }        

    _ntUpdateFileSelector(__state.file_selector);
}


void _ntPVSelectFileUpdate1() {
    renderer_state_t *st = _ntRendererGetState();

    // init text ui environment
    _ntTuiLoadEnvironmentDefault();

    st->layers[0].update = _ntPVSelectFileUpdate;
}

void _ntPVSelectFileDraw() {
    Color gray = (Color){ 30, 30, 30, 255 };

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

    _ntTuiDrawMenu(__state.file_selector->base);

    const char *s1 = "GREEN";
    const char *s2 = "file - possible PE file";

    size_t x = r.x;
    size_t y = r.y + r.height + 1;

    _ntTuiDrawText(s1, x, y, GREEN);
    x += strlen(s1) + 1;

    _ntTuiDrawText(s2, x, y, WHITE);
}

void _ntPVSelectFileMain() {
    int c = GetRenderHeight() / 16 - 7;

    __state.file_selector = _ntLoadFileSelector("./", c);

    RSBAddElementString(__state.file_selector->wanted_fileformats, ".exe");
    RSBAddElementString(__state.file_selector->wanted_fileformats, ".dll");

    _ntFileSelectorSetListing(__state.file_selector);

    __state.file_selector->base.x = 4;
    __state.file_selector->base.y = 3;
    
    __state.file_selector->callback = _ntPVOnFileClick;

    renderer_state_t *st = _ntRendererGetState();

    st->layers[0].draw = _ntPVSelectFileDraw;
    st->layers[0].update = _ntPVSelectFileUpdate1;
}