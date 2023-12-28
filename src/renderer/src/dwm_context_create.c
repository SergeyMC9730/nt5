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

#include <nt5emul/dwm/context.h>
#include <nt5emul/renderer.h>
#include <ini.h>
#include <string.h>
#include <unistd.h>

// Font _ntLoadPixelatedFont(const char *fileName, int fontSize, int *codepoints, int codepointCount) {
//    Font font = { 0 };

//     // Loading file to memory
//     int dataSize = 0;
//     unsigned char *fileData = LoadFileData(fileName, &dataSize);

//     if (fileData != NULL)
//     {
//         // Loading font from memory data
//         font = LoadFontFromMemory(GetFileExtension(fileName), fileData, dataSize, fontSize, codepoints, codepointCount);

//         UnloadFileData(fileData);
//     }
//     else font = GetFontDefault();

//     return font;
// }

void _ntLoadDwmFont(struct dwm_context_font *data, int xsz, float sp, int rsz, const char *font) {
    data->xp_size = xsz;
    data->spacing = sp;
    data->real_size = rsz;

    data->font = LoadFontEx(font, data->real_size, NULL, 0);

    SetTextureFilter(data->font.texture, TEXTURE_FILTER_POINT);
}

void _ntCreateDwmContextMain(struct dwm_context *ctx) {
    // load fonts

    int font_mul = 3;

    _ntLoadDwmFont(&ctx->fonts.tahoma8_std, 8, 1.f, 8 * font_mul, "nt/fonts/tahoma.ttf");
    _ntLoadDwmFont(&ctx->fonts.tahoma8_bld, 8, 1.f, 8 * font_mul, "nt/fonts/tahomabd.ttf");

    font_mul = 2;

    _ntLoadDwmFont(&ctx->fonts.tahoma9_std, 9, 1.f, 9 * font_mul, "nt/fonts/tahoma.ttf");
    _ntLoadDwmFont(&ctx->fonts.tahoma9_bld, 9, 0.5f, 9 * font_mul, "nt/fonts/tahomabd.ttf");

    font_mul = 3;

    _ntLoadDwmFont(&ctx->fonts.franklin24_bld, 9, 1.f, 9 * font_mul, "nt/fonts/framd.ttf");
    
    _ntLoadDwmFont(&ctx->fonts.arial9_std, 9, 1.f, 9 * font_mul, "nt/fonts/arial.ttf");
    
    SetTextureFilter(ctx->fonts.tahoma8_std.font.texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(ctx->fonts.tahoma8_bld.font.texture, TEXTURE_FILTER_POINT);

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