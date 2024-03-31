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

void _ntDwmDrawWithFont(struct dwm_context *ctx, Vector2 pos, Color col, const char *text, const char *font_name) {
    struct dwm_context_font font = _ntDwmGetFont(ctx, font_name);

    if (font.path == NULL) return;

    float font_sz = font.real_size;
    float spacing = font.spacing;

    DrawTextEx(font.font, text, pos, font_sz, spacing, col);
}

void _ntDwmLoadFont(struct dwm_context *ctx, int xsz, float sp, const char *font, const char *name) {
    struct dwm_context_font *data = NULL;

    for (int i = 0; i < 512; i++) {
        if (ctx->fonts.fonts[i].path == NULL || ctx->fonts.fonts[i].name == NULL) {
            data = ctx->fonts.fonts + i;
            break;
        }
    }

    if (data == NULL) return;
    
    renderer_state_t *st = _ntRendererGetState();

    float font_div = 0.6f;
    int rsz = (int)((float)xsz / font_div);
    
    data->xp_size = xsz;
    data->spacing = sp * st->scaling;
    data->real_size = rsz * st->scaling;
    data->path = font;
    data->name = name;

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

#include <string.h>

// get loaded font
struct dwm_context_font _ntDwmGetFont(struct dwm_context *ctx, const char *name) {
    for (int i = 0; i < 512; i++) {
        struct dwm_context_font fnt = ctx->fonts.fonts[i];
        if (fnt.name != NULL && !strcmp(fnt.name, name)) {
            return fnt;
        }
    }

    return (struct dwm_context_font){};
}