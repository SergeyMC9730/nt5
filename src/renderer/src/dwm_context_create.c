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
#include <nt5emul/renderer.h>
#include <ini.h>
#include <string.h>
#include <unistd.h>

void _ntCreateDwmContextMain(struct dwm_context *ctx) {
    // load fonts

    int tahoma_size = 24;

    ctx->fonts.tahoma8_std.xp_size = 8;
    ctx->fonts.tahoma8_std.spacing = 1.f;
    ctx->fonts.tahoma8_std.real_size = tahoma_size;
    ctx->fonts.tahoma8_std.font = LoadFontEx("ntresources/tahoma.ttf", ctx->fonts.tahoma8_std.real_size, NULL, 0);

    ctx->fonts.tahoma8_bld.xp_size = 8;
    ctx->fonts.tahoma8_bld.spacing = 1.f;
    ctx->fonts.tahoma8_bld.real_size = tahoma_size;
    ctx->fonts.tahoma8_bld.font = LoadFontEx("ntresources/tahomabd.ttf", ctx->fonts.tahoma8_bld.real_size, NULL, 0);
    
    // SetTextureFilter(ctx->fonts.tahoma8_std.font.texture, TEXTURE_FILTER_POINT);
    // SetTextureFilter(ctx->fonts.tahoma8_bld.font.texture, TEXTURE_FILTER_POINT);

    // ctx->fonts.tahoma8_std = LoadFontEx("ntresources/tahoma.ttf", 8, NULL, 0);
    // ctx->fonts.tahoma8_bld = LoadFontEx("ntresources/tahomabd.ttf", 8, NULL, 0);

    renderer_state_t *st = _ntRendererGetState();

    st->layers[0].user = NULL;
    st->layers[0].update = NULL;

    ctx->loading_finished = true;
}

// create dwm context
struct dwm_context *_ntCreateDwmContext(const char *theme_path) {
    // allocate context
    struct dwm_context *ctx = (struct dwm_context *)(calloc(1, sizeof(struct dwm_context)));

    // copy theme path string
    char *theme_path_copy = (char *)malloc(strlen(theme_path) + 1);
    strcpy(theme_path_copy, theme_path);

    // create window array
    ctx->windows = RSBCreateArrayDWMWindow();

    ctx->theme.basic.theme_path = (const char *)theme_path_copy;

    // if theme exists parse it
    if (FileExists(theme_path)) {
        // parse this ini file
        ini_parse(theme_path, _ntParseDwmTheme, ctx);
    }

    ctx->theme.basic.title_bar_size = 18;

    renderer_state_t *st = _ntRendererGetState();

    st->layers[0].user = ctx;
    st->layers[0].update = _ntCreateDwmContextMain;

    while (ctx->loading_finished != true) {
        // wait 0.10 seconds before checking again
		usleep(1000000 / 10);
    }

    // return context
    return ctx;
}