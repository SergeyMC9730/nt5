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