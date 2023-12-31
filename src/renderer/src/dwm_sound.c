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

#include <nt5emul/dwm/sound.h>

#include <string.h>

struct dwm_sound _ntDwmLoadSound(const char *path) {
    struct dwm_sound snd = {};

    if (!FileExists(path)) return snd;

    snd.path = path;

    snd.pan = 0.5f;
    snd.pitch = 1.f;
    snd.vol = 0.5f;

    snd.paused.ability = true;
    snd.paused.state = false;

    snd.playing = snd.paused;

    snd.sound = LoadMusicStream(path);

    while (!IsMusicReady(snd.sound)) {}

    snd.length = GetMusicTimeLength(snd.sound);

    SeekMusicStream(snd.sound, 0.f);
    
    SetMusicPan(snd.sound, snd.pan);
    SetMusicPitch(snd.sound, snd.vol);
    SetMusicPitch(snd.sound, snd.pitch);

    _ntDwmStopSound(snd);
}

void _ntDwmUnloadSound(struct dwm_sound snd) {
    if (!snd.sound.ctxData) return;

    UnloadMusicStream(snd.sound);
}

void _ntDwmPlaySound(struct dwm_sound snd) {
    if (!snd.playing.ability) return;

    PlayMusicStream(snd.sound);
}
void _ntDwmStopSound(struct dwm_sound snd) {
    if (!snd.playing.ability) return;

    StopMusicStream(snd.sound);
}
void _ntDwmPauseSound(struct dwm_sound *snd) {
    if (!snd->paused.ability) return;

    snd->playing.state = false;
    snd->paused.state = !snd->paused.state;

    if (snd->paused.state) {
        PauseMusicStream(snd->sound);

        return;
    }

    ResumeMusicStream(snd->sound);
}
void _ntDwmRestartSound(struct dwm_sound *snd) {
    if (!snd->playing.ability) return;

    StopMusicStream(snd->sound);

    snd->played = 0.f;
    SeekMusicStream(snd->sound, snd->played);

    PlayMusicStream(snd->sound);

    snd->paused.state = false;
}

void _ntDwmUpdateSound(struct dwm_sound *snd) {
    SetMusicPan(snd->sound, snd->pan);
    SetMusicPitch(snd->sound, snd->vol);
    SetMusicPitch(snd->sound, snd->pitch);

    UpdateMusicStream(snd->sound);

    if (!snd->playing.ability) return;

    snd->played = GetMusicTimePlayed(snd->sound);
    
    snd->playing.state = IsMusicStreamPlaying(snd->sound);
}

#include <nt5emul/dwm/context.h>

// load sounds from the dwm context
void _ntDwmLoadSounds(struct dwm_context *ctx) {
    ctx->sounds.chimes = LoadSound("nt/sounds/chimes.wav");
    ctx->sounds.chord = LoadSound("nt/sounds/chord.wav");
    ctx->sounds.ding = LoadSound("nt/sounds/ding.wav");
    ctx->sounds.xplogoff = LoadSound("nt/sounds/xplogoff.wav");
    ctx->sounds.xplogon = LoadSound("nt/sounds/xplogon.wav");
    ctx->sounds.xpshutdn = LoadSound("nt/sounds/xpshutdn.wav");
    ctx->sounds.xpstartu = LoadSound("nt/sounds/xpstartu.wav");
}