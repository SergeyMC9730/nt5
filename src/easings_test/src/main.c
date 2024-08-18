/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2024  Sergei Baigerov

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

#include <stdio.h>
#include <nt5emul/renderer.h>
#include <nt5emul/renderer_animation.h>
#include <nt5emul/renderer_keyframe.h>

#define FRAMES 2

struct box_movement {
	struct renderer_animation *new_anim;
} box_animation;

void draw(void *user) {
    ClearBackground(BLACK);

    double x = _ntRendererGetAnimationResult(box_animation.new_anim, 0);
    double y = _ntRendererGetAnimationResult(box_animation.new_anim, 1);

    DrawRectangle(x, y, 40, 40, RED);

    DrawFPS(10, 10);
}
void update(void *user) {
    box_animation.new_anim->delta = (double)1 / (double)GetFPS();

    _ntRendererUpdateAnimation(box_animation.new_anim);
}

void setupAnimationFile() {
	box_animation.new_anim = _ntRendererLoadAnimation("ntresources/anim_test_1.json");

    // _ntRendererPrintAnimationTree(box_animation.new_anim);
}

int main() {
    _ntRendererModifyPreinitOptions(true, true);
    _ntRendererCreateEnvironmentEx(false);

    // SetTargetFPS(30);

    renderer_state_t *st = _ntRendererGetState();

    setupAnimationFile();

    st->layers[0].on_draw.callback = draw;
    st->layers[0].on_update.callback = update;

    _ntRendererJoin();

    return 0;
}
