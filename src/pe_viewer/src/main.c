#include <nt5emul/renderer.h>
#include <nt5emul/pv/select_file.h>
#include <nt5emul/tui/environment.h>

int main() {
    // init NT renderer
	_ntRendererCreateEnvironment();

    int sx = 640;
    int sy = 480;

    SetWindowSize(sx, sy);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(sx, sy);

    SetTargetFPS(30);

    _ntPVSelectFileMain();

    _ntRendererJoin();
}