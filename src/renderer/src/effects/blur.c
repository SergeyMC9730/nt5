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
#include <stdio.h>

// run function  with blur enabled
// if function is not called inside render thread nothing will happen
void _ntRendererApplyBlurEffect(renderer_event_t on_draw) {
    if (!_ntRendererInThread() || !on_draw.callback) return;

    // get renderer state
	renderer_state_t *st = _ntRendererGetState();

    int width_loc = GetShaderLocation(st->blur_shader, "xs");
    int height_loc = GetShaderLocation(st->blur_shader, "ys");
    int radius_loc = GetShaderLocation(st->blur_shader, "r");

    float w = st->current_framebuffer.texture.width;
    float h = st->current_framebuffer.texture.height;

    printf("w=%f; h=%f; wl=%d; hl=%d; rl=%d\n", w, h, width_loc, height_loc, radius_loc);

    SetShaderValue(st->blur_shader, width_loc, &w, SHADER_UNIFORM_FLOAT);
    SetShaderValue(st->blur_shader, height_loc, &h, SHADER_UNIFORM_FLOAT);

    float radius = 5.f;

    SetShaderValue(st->blur_shader, radius_loc, &radius, SHADER_UNIFORM_FLOAT);

    BeginShaderMode(st->blur_shader);
    on_draw.callback(on_draw.user);
    EndShaderMode();
}