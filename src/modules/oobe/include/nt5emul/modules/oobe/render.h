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

#pragma once

void draw_background(void *ctx);
void msoobe_preload(void *ctx);

#include <raylib.h>
#include <nt5emul/modules/oobe/oobe_install_step.h>

void _ntModOobeDrawStretchedTexture(Texture2D texture, bool x_stretched, bool y_stretched, float xstretchmul, float ysctretchmul, Vector2 pos, Vector2 origin);
void _ntModOobeDrawSizedTexture(Texture2D texture, Vector2 size, Vector2 pos, Vector2 origin);

// returns centered texture position (not relative!)
Vector2 _ntModOobeCenterTexture(Texture2D texture, bool x, bool y);

#include <nt5emul/dwm/context.h>

// returns steps length by Y
int _ntModOobeDrawSteps(struct oobe_install_step *steps, unsigned long size);