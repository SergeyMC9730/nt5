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

#include <nt5emul/modules/oobe/auto_progress_bar.h>
#include <nt5emul/modules/oobe/state.h>
#include <raylib.h>

void _ntModOobeUpdateAPB(struct auto_progress_bar *bar) {
    if (bar->progress >= 1.f) {
        bar->progress = 1.f;
        return;
    }

    float step = GetFrameTime() * bar->speed;
    
    bar->progress += step;
}

void _ntModOobeDrawAPB(struct auto_progress_bar bar) {
    Vector2 base_pos = {
        26, GetRenderHeight() - 110
    };
    Vector2 base_size = {
        127, 16
    };

    Vector2 size = base_size;
    Vector2 pos = base_pos;

    DrawRectangleV(pos, size, DARKBLUE);
    
    pos.x++; pos.y++;
    size.x -= 2; size.y -= 2;

    DrawRectangleV(pos, size, WHITE);

    pos.x++; pos.y++;
    size.x = base_size.x * bar.progress - 4;
    size.y -= 2;

    Color green = (Color){
        // 06c100
        .r = 0x06,
        .g = 0xc1,
        .b = 0x00,
        .a = 0xFF
    };

    DrawRectangleV(pos, size, green);

    pos = base_pos;

    struct dwm_context_font font = _state.dwm_ctx->fonts.tahoma9_std;
    
    Vector2 text_sz = MeasureTextEx(font.font, bar.title, font.real_size, font.spacing);

    pos.y -= 1 + text_sz.y;

    DrawTextEx(font.font, bar.title, pos, font.real_size, font.spacing, WHITE);
}