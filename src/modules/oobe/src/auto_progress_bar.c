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
#include <nt5emul/dwm/context.h>

#include <nt5emul/renderer.h>

void _ntModOobeUpdateAPB(struct auto_progress_bar *bar) {
    if (bar->progress >= 1.f) {
        bar->progress = 1.f;
        return;
    }

    float step = GetFrameTime() * bar->speed;
    
    bar->progress += step;
}

void _ntModOobeDrawAPB(struct auto_progress_bar bar) {
    renderer_state_t *st = _ntRendererGetState();

    Vector2 base_pos = {
        26 * st->scaling, st->current_window_size.y - (110 * st->scaling)
    };
    Vector2 base_size = {
        127 * st->scaling, 16 * st->scaling
    };

    Vector2 size = base_size;
    Vector2 pos = base_pos;

    DrawRectangleV(pos, size, DARKBLUE);
    
    pos.x += 1 * st->scaling; pos.y += 1 * st->scaling;
    size.x -= 2 * st->scaling; size.y -= 2 * st->scaling;

    DrawRectangleV(pos, size, WHITE);

    pos.x += 1 * st->scaling; pos.y += 1 * st->scaling;
    size.x = base_size.x * bar.progress - (4 * st->scaling);
    size.y -= 2 * st->scaling;

    Color green = (Color){
        // 06c100
        .r = 0x06,
        .g = 0xc1,
        .b = 0x00,
        .a = 0xFF
    };

    DrawRectangleV(pos, size, green);

    pos = base_pos;

    struct dwm_context_font font = _ntDwmGetFont(_state.dwm_ctx, "tahoma9");
    
    Vector2 text_sz = MeasureTextEx(font.font, bar.title, font.real_size, font.spacing);

    pos.y -= (1.f * st->scaling) + text_sz.y;

    DrawTextEx(font.font, bar.title, pos, font.real_size, font.spacing, WHITE);
}