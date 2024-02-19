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

#include <nt5emul/renderer_ease.h>

void _ntRendererProcessTweakDouble(renderer_double_tweak_object_t *tweak) {
    double (*easings[TOEnd])(double) = {
        _rendererLinear, _rendererInSine, _rendererOutSine,
        _rendererInOutSine, _rendererInQuad, _rendererOutQuad,
        _rendererInOutQuad, _rendererInCubic, _rendererOutCubic,
        _rendererInOutCubic, _rendererInQuart, _rendererOutQuart,
        _rendererInOutQuart, _rendererInQuint, _rendererOutQuint,
        _rendererInOutQuint, _rendererInExpo, _rendererOutExpo,
        _rendererInOutExpo, _rendererInCirc, _rendererOutCirc,
        _rendererInOutCirc, _rendererInBack, _rendererOutBack,
        _rendererInOutBack, _rendererInElastic, _rendererOutElastic,
        _rendererInOutElastic, _rendererInBounce, _rendererOutBounce,
        _rendererInOutBounce 
    };

    if (tweak->obj.type > TOEnd) return;
    if (tweak->obj.passed > 1.0) return;

    double (*ease)(double) = easings[tweak->obj.type];
    if (!ease) return;

    double delta = (double)GetFrameTime() / tweak->obj.time;
    tweak->obj.passed += delta;

    double val = ease(tweak->obj.passed);
    *tweak->val += val * tweak->obj.power;

    return; 
}