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

#include <nt5emul/dwm/button.h>

// if user clicks to button function returns true
bool _ntDrawDWMButton(struct dwm_context *ctx, struct dwm_button *btn) {
    Vector2 mouse = GetMousePosition();

    Texture2D used_texture = btn->off;

    // check if button can be activated
    btn->activated.state = IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, btn->button) && btn->activated.ability;

    // check if user presses the button but not releases yes
    btn->howered.state = IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, btn->button) && btn->howered.ability;

    if (btn->howered.state) {
        used_texture = btn->on;
    }

    // if (btn->howered = false)

    Rectangle sz = btn->button;

    float font_sz = ctx->fonts.tahoma8_bld.real_size * 0.5f;
    float spacing = ctx->fonts.tahoma8_bld.spacing;

    Vector2 szText = MeasureTextEx(ctx->fonts.tahoma8_bld.font, btn->text, font_sz, spacing);

    int alignY = (sz.height - szText.y) / 2;
    int alignX = (sz.width - szText.x) / 2;

    Color borders[4] = {
        ctx->theme.basic.active_border_color,
        ctx->theme.basic.window_base_color,
        ctx->theme.basic.button_dk_shadow,
        ctx->theme.basic.button_shadow_color
    };

    Color border1, border2, border3, border4;

    Vector2 text_pos = {
        btn->button.x + alignX,
        btn->button.y + alignY
    };

    if (btn->howered.state) {
        border1 = borders[0];
        border2 = borders[2];

        border3 = borders[3];
        border4 = borders[1];

        text_pos.x++;
        text_pos.y++;
    } else {
        border1 = borders[0];
        border2 = borders[1];

        border3 = borders[2];
        border4 = borders[3];
    }

    DrawLine(sz.x, sz.y, sz.x + sz.width - 1, sz.y, border1);
    DrawLine(sz.x, sz.y, sz.x, sz.y + sz.height, border1);

    DrawLine(sz.x - 1, sz.y + sz.height, sz.x + sz.width, sz.y + sz.height, border3);
    DrawLine(sz.x + sz.width, sz.y + sz.height, sz.x + sz.width, sz.y, border3);

    DrawLine(sz.x + 1, sz.y + 1, sz.x + sz.width - 2, sz.y + 1, border2);
    DrawLine(sz.x + 1, sz.y + 1, sz.x + 1, sz.y + sz.height - 1, border2);

    DrawLine(sz.x - 1 + 1, sz.y + sz.height - 1, sz.x + sz.width - 1, sz.y + sz.height - 1, border4);
    DrawLine(sz.x + sz.width - 1, sz.y + sz.height - 1, sz.x + sz.width - 1, sz.y + 1, border4);

    DrawRectangle(sz.x + 1, sz.y + 2, sz.width - 3, sz.height - 3, border1);

    if (used_texture.width != 0 && used_texture.height != 0) {
        int alignTY = (sz.height - used_texture.width) / 2;
        int alignTX = (sz.width - used_texture.height) / 2;

        Vector2 texture_pos = {
            btn->button.x + alignTX,
            btn->button.y + alignTY
        };

        DrawTexture(used_texture, texture_pos.x, texture_pos.y, WHITE);
    }

    if (btn->text) {
        // printf("drawing %s at %f:%f\n", btn->text, text_pos.x, text_pos.y);

        DrawTextEx(ctx->fonts.tahoma8_bld.font, btn->text, (Vector2){
            text_pos.x, text_pos.y
        }, font_sz, spacing, BLACK);
    }

    return btn->activated.state;
}