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

#include <nt5emul/renderer.h>
#include <raylib.h>

void _ntRendererDrawCroppedTexture(Texture2D texture, Vector2 crop, Vector2 pos) {
    Rectangle source = {
        .x = 0,
        .y = 0,
        .width = texture.width,
        .height = texture.height
    };

    Rectangle dest = {
        .x = pos.x,
        .y = pos.y,
        .width = source.width,
        .height = source.height
    };

    DrawTexturePro(texture, source, dest, (Vector2){}, 0.f, WHITE);
}

#include <nt5emul/middle.h>

Vector2 _ntRendererCenterTexture(Texture2D texture, bool x, bool y) {
    renderer_state_t *st = _ntRendererGetState();

    Vector2 sz = {
        st->current_window_size.x,
        st->current_window_size.y
    };

    Vector2 pos = {
        _ntGetMiddleValue(texture.width, sz.x),
        _ntGetMiddleValue(texture.height, sz.y)
    };

    return pos;
}

void _ntRendererDrawSizedTexture(Texture2D texture, Vector2 size, Vector2 pos, Vector2 origin, bool inside_scale) {
    Rectangle source = {
        .x = 0,
        .y = 0,
        .width = texture.width * (1.f / size.x),
        .height = texture.height * (1.f / size.y)
    };

    Rectangle dest = {
        .x = pos.x,
        .y = pos.y,
        .width = texture.width,
        .height = texture.height
    };

    if (!inside_scale) {
        source = (Rectangle){
            .x = 0,
            .y = 0,
            .width = texture.width,
            .height = texture.height
        };

        dest = (Rectangle){
            .x = pos.x,
            .y = pos.y,
            .width = texture.width * size.x,
            .height = texture.height * size.y
        };
    }

    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}

void _ntRendererDrawStretchedTexture(Texture2D texture, bool x_stretched, bool y_stretched, float xstretchmul, float ysctretchmul, Vector2 pos, Vector2 origin) {
    renderer_state_t *st = _ntRendererGetState();
    
    Vector2 sz = {
        .x = st->current_window_size.x,
        .y = st->current_window_size.y
    };

    Rectangle source = {
        .x = 0,
        .y = 0,
        .width = texture.width,
        .height = texture.height
    };

    Rectangle dest = {
        .x = pos.x,
        .y = pos.y,
        .width = source.width,
        .height = source.height
    };

    if (x_stretched) {
        dest.width = sz.x * xstretchmul;
    }
    if (y_stretched) {
        dest.height = sz.y * ysctretchmul;
    }

    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}