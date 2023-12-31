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

#include <raylib.h>
#include <nt5emul/dwm/bool.h>

struct dwm_sound {
    const char *path;

    Music sound;

    float vol;
    float pitch;
    float pan;

    float length;
    float played;
    
    struct dwm_bool paused;
    struct dwm_bool playing;
};

struct dwm_sound _ntDwmLoadSound(const char *path);
void _ntDwmUnloadSound(struct dwm_sound snd);

void _ntDwmPlaySound(struct dwm_sound snd);
void _ntDwmStopSound(struct dwm_sound snd);
void _ntDwmPauseSound(struct dwm_sound *snd);
void _ntDwmRestartSound(struct dwm_sound *snd);

void _ntDwmUpdateSound(struct dwm_sound *snd);