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

#include <nt5emul/modules/oobe/setup_command.h>
#include <nt5emul/modules/oobe/state.h>
#include <nt5emul/modules/oobe/render.h>

#include <nt5emul/renderer.h>

#include <nt5emul/timer.h>

void setup_decrement_time(void *ctx) {
    _state.minutes_left -= 10;
}

#include <unistd.h>
#include <nt5emul/nt_config.h>

void setup_exit(void *ctx) {
    // get renderer state
    renderer_state_t *st = _ntRendererGetState();

    int layer_index = 0;
    // get layer at index 0
    renderer_layer_t *layer = st->layers + layer_index;

    // recover old layer
    layer->update = _state.old_update;
    layer->draw = _state.old_draw;
    layer->user = _state.old_ctx;

    // creating texture list as pointers to save stack space
    Texture2D *textures[] = {
        &_state.line_bottom_texture, &_state.line_top_texture,
        &_state.logo_texture, &_state.main_bg_texture,
        &_state.radio_off_texture, &_state.radio_on_texture
    };

    // get array size
    size_t sz = sizeof(textures) / sizeof(Texture2D *);

    for (size_t i = 0; i < sz; i++) {
        // unload each texture
        UnloadTexture(textures[i][0]);
    }

    const char *config_path = "nt/config.json";

    // read config
    struct nt_config config = _ntGetConfig(config_path);

    // set value
    config.graphical_setup_completed = true;

    // save config
    _ntSaveConfig(config, config_path);
}

void setup_exit_queue(void *ctx) {
    // unload all textures on the next frame and recover old layer parameters
    _ntRendererPushQueue(setup_exit, NULL);
}

bool setup_command(void *data) {
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

    // period count
    int times = 4;
    // how long each period would be
    int mul = 3;

    // set minutes left value
    _state.minutes_left = times * 10;

    layer->draw = draw_background;

    // load all textures before rendering oobe layer
    _ntRendererPushQueue(setup_preload, NULL);

    for (int i = 0; i < times; i++) {
        // install timer for time decrementing
        _ntInstallTimer(setup_decrement_time, (i + 1) * mul);
        // wait 0.1s
        usleep(10000);
    }

    // install unloading timer
    _ntInstallTimer(setup_exit_queue, (times + 1) * mul);

    return true;
}