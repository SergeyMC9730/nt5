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

int _ntModOobeDrawSteps(struct oobe_install_step *steps, unsigned long size) {    
    Vector2 base_pos = {
        27, 63
    };

    int length = 0;

    for (unsigned long i = 0; i < size; i++) {
        struct oobe_install_step step = steps[i];
        
        // get disabled radio texture
        Texture2D txt = _state.radio_off_texture;

        // set default text color to WHITE
        Color text_color = WHITE;
        
        // get standard tahoma font from the DWM
        struct dwm_context_font font = _state.dwm_ctx->fonts.tahoma9_std;

        // check if this step is done
        if (step.done) {
            // set texture to the activated radio one
            txt = _state.radio_on_texture;

            // set font to be bold
            font = _state.dwm_ctx->fonts.tahoma9_bld;
        }

        // check if this step is selected
        if (step.selected) {
            // set texture color to ORANGE
            text_color = ORANGE;

            // set font to be bold
            font = _state.dwm_ctx->fonts.tahoma9_bld;
        }

        // draw texture
        DrawTextureV(txt, base_pos, WHITE);

        // calculate text position based on the base position
        Vector2 text_pos = {
            base_pos.x + txt.width + 12,
            base_pos.y + 1
        };

        // draw step text
        DrawTextEx(font.font, step.name, text_pos, font.real_size, font.spacing, text_color);

        // increment base pos y by texture height plus 20 pixels
        base_pos.y += txt.height + 20;

        length = base_pos.y;
    }

    return length;
}