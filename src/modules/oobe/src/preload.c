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

#include <nt5emul/modules/oobe/state.h>

void msoobe_preload(void *ctx) {
    _state.logo_texture = LoadTexture("nt/images/user/ui/mslogo.jpg");
    _state.main_bg_texture = LoadTexture("nt/images/user/ui/newmark1.jpg");
    _state.line_bottom_texture = LoadTexture("nt/images/user/ui/newbtm1.jpg");
    _state.line_top_texture = LoadTexture("nt/images/user/ui/newtop1.jpg");

    // TEMP

    _state.radio_off_texture = LoadTexture("nt/images/user/ui/nextdown.jpg");
    _state.radio_on_texture = LoadTexture("nt/images/user/ui/nextover.jpg");

    // texture wraps

    SetTextureWrap(_state.main_bg_texture, TEXTURE_WRAP_CLAMP);
    // SetTextureWrap(_state.logo_texture, TEXTURE_WRAP_);

    // window settings

    SetWindowSize(800, 600);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(640, 480);

    // texture filters

    SetTextureFilter(_state.logo_texture, TEXTURE_FILTER_BILINEAR);
}