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

#include <nt5emul/modules/oobe/msoobe_command.h>
#include <nt5emul/modules/oobe/state.h>

#include <nt5emul/modules/oobe/render.h>

#include <nt5emul/renderer.h>

#include <nt5emul/timer.h>

void msoobe_draw(void *ctx) {
    _ntModOobeDrawStretchedTexture(_state.xp_vid.texture, true, true, 1.f, 1.f, (Vector2){0, 0}, (Vector2){0, 0});
}
void msoobe_update(void *ctx) {
    _ntDwmUpdateVideo(_state.xp_vid);

    if (_state.frame_1 != -1) {
        _state.frame_2 = _state.frame_1;
        _state.frame_1 = _state.xp_vid.stream->codecContext->frame_number;
    }

    if (_state.frame_1 == _state.frame_2) {
        SetTargetFPS(_state.old_fps);
        _state.frame_1 = -1;
    }
}

void msoobe_recover_fps(void *ctx) {
    SetTargetFPS(_state.old_fps);
}

void msoobe_preload(void *ctx) {
    _state.xp_vid = _ntDwmLoadVideo("nt/videos/user/intro.wmv");
    _state.old_fps = (1.f / GetFrameTime()) + 1;

    SetTextureFilter(_state.xp_vid.texture, TEXTURE_FILTER_BILINEAR);

    SetTargetFPS(15);
}

bool msoobe_command(void *data) {
    // get renderer state
    renderer_state_t *st = _ntRendererGetState();

    int layer_index = 0;

    // get layer pointer at index of 0
    renderer_layer_t *layer = st->layers + layer_index;

    // save old layer
    _state.old_draw = layer->draw;
    _state.old_update = layer->update;
    _state.old_ctx = layer->user;

    // get dwm context from the user input
    _state.dwm_ctx = data;

    layer->draw = msoobe_draw;
    layer->update = msoobe_update;

    // load all textures before rendering oobe layer
    _ntRendererPushQueue(msoobe_preload, NULL);
    
    InitAudioDevice();

    _state.music_title = LoadSound("nt/sounds/title.mp3");

    PlaySound(_state.music_title);

    _ntDwmLoadSounds(_state.dwm_ctx);

    return true;
}