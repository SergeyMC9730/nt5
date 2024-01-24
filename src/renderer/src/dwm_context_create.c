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

void _ntLoadDwmFont(struct dwm_context_font *data, int xsz, float sp, int rsz, const char *font) {
    renderer_state_t *st = _ntRendererGetState();
    
    data->xp_size = xsz;
    data->spacing = sp *= st->scaling;
    data->real_size = rsz *= st->scaling;

    const char *_ntTuiCodepoints =  "QWERTYUIOPASDFGHJKLZXCVBNM" // english alphabet with all upper case characters
                                "qwertyuiopasdfghjklzxcvbnmzxcvbnm" // english alphabet with all lower case characters
                                "[]{}()" // brackets
                                "ЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ" // cyrillic alphabet with all upper case characters
                                "ёйцукенгшщзхъфывапролджэячсмитьбю" // cyrillic alphabet with all lower case chararcters
                                ",.;!?:" // punctuation      
                                "/\\|" // slashes
                                "1234567890" // numbers
                                "<>-=+~*^%№" // math signs
                                "\"'`" // quotation marks
                                "@#$&_"; // random characters

    int codepointCount = 0;
    int *codepoints = LoadCodepoints(_ntTuiCodepoints, &codepointCount);

    data->font = LoadFontEx(font, data->real_size, codepoints, codepointCount);

    SetTextureFilter(data->font.texture, TEXTURE_FILTER_BILINEAR);

    free(codepoints);
}

void _ntCreateDwmContextMain(struct dwm_context *ctx) {
    // load fonts

    float font_div = 0.6f;
    
    _ntLoadDwmFont(&ctx->fonts.tahoma8_std, 8, 0.5f, 8.f / font_div, "nt/fonts/tahoma.ttf");
    _ntLoadDwmFont(&ctx->fonts.tahoma8_bld, 8, 0.5f, 8.f / font_div, "nt/fonts/tahomabd.ttf");

    _ntLoadDwmFont(&ctx->fonts.tahoma9_std, 9, 0.5f, 9.f / font_div, "nt/fonts/tahoma.ttf");
    _ntLoadDwmFont(&ctx->fonts.tahoma9_bld, 9, 0.5f, 9.f / font_div, "nt/fonts/tahomabd.ttf");

    _ntLoadDwmFont(&ctx->fonts.tahoma12_std, 12, 0.5f, 12.f / font_div, "nt/fonts/tahoma.ttf");
    _ntLoadDwmFont(&ctx->fonts.tahoma12_bld, 12, 0.5f, 12.f / font_div, "nt/fonts/tahomabd.ttf");

    _ntLoadDwmFont(&ctx->fonts.franklin24_std, 24, 0.5f, 24.f / font_div, "nt/fonts/framd.ttf");
    _ntLoadDwmFont(&ctx->fonts.franklin24_bld, 24, 0.5f, 24.f / font_div, "nt/fonts/framd.ttf");
    
    _ntLoadDwmFont(&ctx->fonts.arial9_std, 9, 0.5f, 9.f / font_div, "nt/fonts/arial.ttf");

    renderer_state_t *st = _ntRendererGetState();

    st->layers[0].user = NULL;
    st->layers[0].update = NULL;

    if (!ctx->sounds.audio_device_initialized)  {
        InitAudioDevice();

        ctx->sounds.audio_device_initialized = true;
    }

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

    renderer_state_t *st = _ntRendererGetState();

    ctx->theme.basic.title_bar_size = 18 * st->scaling;

    st->layers[0].user = ctx;
    st->layers[0].update = _ntCreateDwmContextMain;

    ctx->lpack = _ntGenerateLanguagePack();

    while (ctx->loading_finished != true) {
        // wait 0.10 seconds before checking again
		usleep(1000000 / 10);
    }

    // return context
    return ctx;
}