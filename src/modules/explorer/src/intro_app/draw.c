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

#include <nt5emul/modules/explorer/state.h>
#include <nt5emul/dwm/context.h>
#include <nt5emul/renderer.h>
#include <nt5emul/dwm/window.h>
#include <nt5emul/tui/text.h>

#ifndef NULL
#define NULL (void *)0
#endif

#include <stdio.h>

void explorer_intro_draw(struct dwm_window *wnd, void *user) {
    struct dwm_context *ctx = _ntDwmGetGlobal();
    struct local_module_state *lst = (struct local_module_state *)user;
    renderer_state_t *st = _ntRendererGetState();

    ClearBackground(BLANK);

    struct dwm_context_font small_font = _ntDwmGetFont(ctx, "tahoma12");

    Color shadow = {
        .r = 0x00,
        .g = 0x00,
        .b = 0x00,
        .a = 0xFF / 2
    };

    DrawTextEx(small_font.font, _state.cterm_shell_intro_text, (Vector2){11 * st->scaling, 6 * st->scaling}, small_font.real_size, small_font.spacing, shadow);
    DrawTextEx(small_font.font, _state.cterm_shell_intro_text, (Vector2){10 * st->scaling, 5 * st->scaling}, small_font.real_size, small_font.spacing, BLACK);
}