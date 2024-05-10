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

#include <nt5emul/dwm/context.h>

#include <string.h>

// destroy dwm context
void _ntDwmDestroyContext(struct dwm_context *ctx) {
    // free theme path string
    free((char *)ctx->theme.basic.theme_path);

    // destroy windows
    rsb_array_Int *windows = _ntDwmGetProcessesRaw(ctx);
    
    for (int i = 0; i < windows->len; i++) {
        struct dwm_window *wnd = _ntDwmGetProcess(ctx, RSBGetAtIndexInt(windows, i));

        _ntCloseWindow(wnd, ctx);
    }

    RSBDestroyInt(windows);
    RSBDestroyDWMWindow(ctx->windows);
    RSBDestroyEvent(ctx->window_create_event);

    // unload fonts
    // struct dwm_context_font *fonts[] = {
    //     &ctx->fonts.tahoma12_bld, &ctx->fonts.tahoma12_std,
    //     &ctx->fonts.tahoma9_bld, &ctx->fonts.tahoma9_std,
    //     &ctx->fonts.tahoma8_bld, &ctx->fonts.tahoma8_std,
    //     &ctx->fonts.arial9_std, &ctx->fonts.franklin24_bld,
    //     &ctx->fonts.franklin24_std, &ctx->fonts.lucidacon10_std,
    //     &ctx->fonts.lucidacon10_std
    // };

    // for (int i = 0; i < sizeof(fonts) / sizeof(struct dwm_context_font *); i++) {
    //     struct dwm_context_font *font = fonts[i];

    //     UnloadFont(font->font);
    // }

    // free context
    free(ctx);
}