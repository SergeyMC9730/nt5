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
#include <cterm/cterm_command_line.h>
#include <nt5emul/renderer.h>
#include <cterm/cterm.h>
#include <nt5emul/timer.h>
#include <nt5emul/dwm/context.h>

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
    *layer = _state.old_layer;

    // creating texture list as pointers to save stack space
    Texture2D *textures[] = {
        &_state.logo_texture, &_state.main_bg_texture, &_state.line_bottom_texture,
        &_state.line_top_texture, &_state.radio_off_texture, &_state.radio_on_texture,
        &_state.square_next_texture_off, &_state.square_next_texture_on, &_state.square_skip_texture_off,
        &_state.square_skip_texture_on
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

    // free config
    _ntUnloadConfig(config);

    // send notification

    struct cterm_execute_result result;
    _ctermExecute(_state.runtime, "notify Restarting...", &result);

    _state.execution_lock = false;

    // period count
    int times = 2;
    // set minutes left value
    _state.minutes_left = times * 10;

    // reset progress bar value
    _state.current_bar = 0;

    setup_reset_bars();

    // stop title.wma (title.mp3)
    StopSound(_state.music_title);
}

void setup_exit_queue(void *ctx) {
    // unload all textures on the next frame and recover old layer parameters
    _ntRendererPushQueue(setup_exit, NULL);
}

bool setup_command(struct cterm_command *data) {
    if (_state.execution_lock) {
        printf("error: only a single setup process can be run at the same time\n");

        return false;
    }

    _state.execution_lock = true;
    _state.runtime = data->linked_instance;

    // get renderer state
    renderer_state_t *st = _ntRendererGetState();

    int layer_index = 0;

    // get layer pointer at index of 0
    renderer_layer_t *layer = st->layers + layer_index;

    // save old layer
    _state.old_layer = *layer;

    // get global dwm context
    _state.dwm_ctx = _ntDwmGetGlobal();

    // period count
    int times = 2;
    // how long each period would be
    int mul = 3;

    // set minutes left value
    _state.minutes_left = times * 10;

    layer->on_draw.callback = draw_background;

    // load all textures before rendering oobe layer
    _ntRendererPushQueue(setup_preload, NULL);

    struct nt_config cfg = _ntGetConfig("nt/config.json");

    const char *lang = cfg.selected_lang;

    // free config
    _ntUnloadConfig(cfg);

    _state.cterm_setup_installing_devices = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_setup_installing_devices", lang);
    _state.cterm_setup_installing_network = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_setup_installing_network", lang);
    _state.cterm_setup_copying_files = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_setup_copying_files", lang);
    _state.cterm_setup_completing_install = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_setup_completing_install", lang);
    _state.cterm_setup_installing_start = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_setup_installing_start", lang);
    _state.cterm_setup_saving_settings = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_setup_saving_settings", lang);
    _state.cterm_setup_time_approx = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_setup_time_approx", lang);
    _state.cterm_setup_colinfo = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_setup_colinfo", lang);
    _state.cterm_setup_dynupd = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_setup_dynupd", lang);
    _state.cterm_setup_instwin = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_setup_instwin", lang);
    _state.cterm_setup_final = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_setup_final", lang);
    _state.cterm_setup_prepinst = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_setup_prepinst", lang);
    _state.cterm_setup_registering_components = _ntGetStringInLanguagePack(_state.dwm_ctx->lpack, "cterm_setup_registering_components", lang);

    for (int i = 0; i < times; i++) {
        // install timer for time decrementing
        _ntInstallTimer(setup_decrement_time, (i + 1) * mul, NULL);
        // wait 0.1s
        _ntSetupTimerSync(0.1);
    }

    // install unloading timer
    _ntInstallTimer(setup_exit_queue, (times + 1) * mul, NULL);

    return true;
}