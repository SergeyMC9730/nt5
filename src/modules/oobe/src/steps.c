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
#include <nt5emul/modules/oobe/render.h>

void _ntModOobeDrawSteps(struct oobe_install_step *steps, unsigned long size) {
    Vector2 base_pos = {
        27, 63
    };

    for (unsigned long i = 0; i < size; i++) {
        struct oobe_install_step step = steps[i];
        
        Texture2D txt = _state.radio_off_texture;
        Color text_color = WHITE;

        if (step.done) {
            txt = _state.radio_on_texture;
            text_color = ORANGE;
        }

        DrawTextureV(txt, base_pos, WHITE);

        struct dwm_context_font font = _state.dwm_ctx->fonts.tahoma9_bld;

        Vector2 text_pos = {
            base_pos.x + txt.width + 8,
            base_pos.y + 1
        };

        DrawTextEx(font.font, step.name, text_pos, font.real_size, font.spacing, text_color);
    }
}