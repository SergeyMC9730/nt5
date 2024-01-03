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

void setup_preload(void *ctx) {
    _state.logo_texture = LoadTexture("nt/images/user/ui/mslogo.jpg");
    _state.main_bg_texture = LoadTexture("nt/images/user/ui/newmark1.jpg");
    _state.line_bottom_texture = LoadTexture("nt/images/user/ui/newbtm1.jpg");
    _state.line_top_texture = LoadTexture("nt/images/user/ui/newtop1.jpg");

    // TEMP
    _state.radio_off_texture = LoadTexture("nt/images/user/ui/nextdown.jpg");
    _state.radio_on_texture = LoadTexture("nt/images/user/ui/nextover.jpg");

    _state.square_next_texture_off = LoadTexture("nt/images/user/ui/nextup.jpg");
    _state.square_next_texture_on = LoadTexture("nt/images/user/ui/nextdown.jpg");

    _state.square_skip_texture_off = LoadTexture("nt/images/user/ui/skipup.jpg");
    _state.square_skip_texture_on = LoadTexture("nt/images/user/ui/skipdown.jpg");

    // texture wraps
    SetTextureWrap(_state.main_bg_texture, TEXTURE_WRAP_CLAMP);

    // window settings
    SetWindowSize(640, 480);

    // texture filters
    Texture2D *texture_list[] = {
        &_state.logo_texture, &_state.main_bg_texture, &_state.line_bottom_texture,
        &_state.line_top_texture, &_state.radio_off_texture, &_state.radio_on_texture,
        &_state.square_next_texture_off, &_state.square_next_texture_on, &_state.square_skip_texture_off,
        &_state.square_skip_texture_on
    };

    size_t list_sz = sizeof(texture_list) / sizeof(Texture2D *);

    for (size_t i = 0; i < list_sz; i++) {
        Texture2D *txt = texture_list[i];

        SetTextureFilter(*txt, TEXTURE_FILTER_BILINEAR);
    }
}