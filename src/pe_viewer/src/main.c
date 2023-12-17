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