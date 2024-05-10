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

#include <nt5emul/renderer_animation.h>
#include <nt5emul/renderer_keyframe.h>
#include <raylib.h>

struct sidebar_state {
    Vector2 pos;
    const char *title;
    const char **elements;

    struct renderer_animation anim;
    struct renderer_keyframe frame;

    bool closed;

    float content_height;
};

struct local_module_state {
    int id;

    struct sidebar_state bar1;
    struct sidebar_state bar2;
};