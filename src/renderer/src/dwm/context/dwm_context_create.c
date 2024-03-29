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
// #include <freetype-gl.h>

void _ntRendererLoadShaders() {
    // i hate stack.

    // _ntRendererThread cannot handle this function
    // and causes stack to work very strangely.
    // in this case `sh` variable would be zeroed or
    // have garbage data no matter what LoadShader
    // would return.

    // i literally had to move this function into the
    // dwm loading routine so the shader value would
    // not be broken by this pthread insanity.
    // when i moved this piece of code into the dwm
    // code it magically worked.

    renderer_state_t *st = _ntRendererGetState();

	// load blur effect
	const char *fsFileName = "ntresources/blur/blur.fs";
	const char *vsFileName = NULL;

	Shader sh = LoadShader(vsFileName, fsFileName);
	
	printf("---- SHADER ID = %d ----\n", sh.id);
	printf("---- SHADER LOCS = %p ----\n", sh.locs);

    for (int i = 0; i < 5; i++) {
        printf("loc %d = %d\n", i, sh.locs[i]);
    }

    st->blur_shader.id = sh.id;
    st->blur_shader.locs = sh.locs;
    st->blur_shader_ptr = sh.locs;
}

void _ntDwmLoadFont(struct dwm_context_font *data, int xsz, float sp, int rsz, const char *font) {
    renderer_state_t *st = _ntRendererGetState();
    
    data->xp_size = xsz;
    data->spacing = sp *= st->scaling;
    data->real_size = rsz *= st->scaling;
    data->path = font;

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
    
    _ntDwmLoadFont(&ctx->fonts.tahoma8_std, 8, 0.5f, 8.f / font_div, "nt/fonts/tahoma.ttf");
    _ntDwmLoadFont(&ctx->fonts.tahoma8_bld, 8, 0.5f, 8.f / font_div, "nt/fonts/tahomabd.ttf");

    _ntDwmLoadFont(&ctx->fonts.tahoma9_std, 9, 0.5f, 9.f / font_div, "nt/fonts/tahoma.ttf");
    _ntDwmLoadFont(&ctx->fonts.tahoma9_bld, 9, 0.5f, 9.f / font_div, "nt/fonts/tahomabd.ttf");

    _ntDwmLoadFont(&ctx->fonts.tahoma12_std, 12, 0.5f, 12.f / font_div, "nt/fonts/tahoma.ttf");
    _ntDwmLoadFont(&ctx->fonts.tahoma12_bld, 12, 0.5f, 12.f / font_div, "nt/fonts/tahomabd.ttf");

    _ntDwmLoadFont(&ctx->fonts.franklin24_std, 24, 0.5f, 24.f / font_div, "nt/fonts/framd.ttf");
    _ntDwmLoadFont(&ctx->fonts.franklin24_bld, 24, 0.5f, 24.f / font_div, "nt/fonts/framd.ttf");
    
    _ntDwmLoadFont(&ctx->fonts.arial9_std, 9, 0.5f, 9.f / font_div, "nt/fonts/arial.ttf");

    _ntDwmLoadFont(&ctx->fonts.lucidacon10_std, 10, 0.5f, 10.f / font_div, "nt/fonts/lucon.ttf");

    renderer_state_t *st = _ntRendererGetState();

    st->layers[0] = (renderer_layer_t){};

    if (!ctx->sounds.audio_device_initialized)  {
        InitAudioDevice();

        ctx->sounds.audio_device_initialized = true;
    }

    _ntRendererLoadShaders();

    ctx->loading_finished = true;
}

#include <nt5emul/timer.h>

// create dwm context
struct dwm_context *_ntDwmCreateContext(const char *theme_path) {
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

    st->layers[0].on_update.user = ctx;
    st->layers[0].on_update.callback = _ntCreateDwmContextMain;

    ctx->lpack = _ntGenerateLanguagePack();

    while (ctx->loading_finished != true) {
        // wait 0.1 seconds before checking again
		_ntSetupTimerSync(0.01);
    }

    _ntRendererAddCloseEvent(_ntDwmDestroyContext, ctx, false);

    // return context
    return ctx;
}