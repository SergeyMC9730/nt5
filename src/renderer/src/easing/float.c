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

void _ntRendererProcessTweakFloat(renderer_float_tweak_object_t *tweak) {
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

    float delta = GetFrameTime() / (float)tweak->obj.time;
    tweak->obj.passed += delta;

    float val = 1.f - (float)ease(tweak->obj.passed);
    *tweak->val += tweak->orig * val * tweak->obj.power * delta;

    return; 
}