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

#include <nt5emul/dwm/context.h>
#include <ini.h>
#include <nt5emul/renderer.h>
#include <string.h>
#include <unistd.h>

void _ntCreateDwmContextMain(struct dwm_context *ctx) {
    // load fonts

    float font_div = 0.6f;
    
    _ntDwmLoadFont(ctx, 8, 0.5f, "nt/fonts/tahoma.ttf", "tahoma8");
    _ntDwmLoadFont(ctx, 8, 0.5f, "nt/fonts/tahomabd.ttf", "tahomabd8");

    _ntDwmLoadFont(ctx, 9, 0.5f, "nt/fonts/tahoma.ttf", "tahoma9");
    _ntDwmLoadFont(ctx, 9, 0.5f, "nt/fonts/tahomabd.ttf", "tahomabd9");

    _ntDwmLoadFont(ctx, 12, 0.5f, "nt/fonts/tahoma.ttf", "tahoma12");
    _ntDwmLoadFont(ctx, 12, 0.5f, "nt/fonts/tahomabd.ttf", "tahomabd12");

    _ntDwmLoadFont(ctx, 24, 0.5f, "nt/fonts/framd.ttf", "framd24");
    
    _ntDwmLoadFont(ctx, 9, 0.5f, "nt/fonts/arial.ttf", "arial9");

    _ntDwmLoadFont(ctx, 10, 0.5f, "nt/fonts/lucon.ttf", "lucon10");

    renderer_state_t *st = _ntRendererGetState();

    st->layers[0] = (renderer_layer_t){};

    if (!ctx->sounds.audio_device_initialized)  {
        InitAudioDevice();

        ctx->sounds.audio_device_initialized = true;
    }

    ctx->loading_finished = true;
}

#include <nt5emul/timer.h>

#define register_lua_func(func) lua_register(st->lua_interpreter, #func, _ntDwmLua##func);

#include <nt5emul/dwm/lua_bindings.h>

// create dwm context
struct dwm_context *_ntDwmCreateContext(const char *theme_path) {
    // allocate context
    struct dwm_context *ctx = (struct dwm_context *)(calloc(1, sizeof(struct dwm_context)));

    // copy theme path string
    char *theme_path_copy = (char *)malloc(strlen(theme_path) + 1);
    strcpy(theme_path_copy, theme_path);

    // create window array
    ctx->windows = RSBCreateArrayDWMWindow();

    ctx->theme.basic.theme_path = (const char *)theme_path_copy;

    // if theme exists parse it
    if (FileExists(theme_path)) {
        // parse this ini file
        ini_parse(theme_path, _ntParseDwmTheme, ctx);
    }

    renderer_state_t *st = _ntRendererGetState();

    ctx->theme.basic.title_bar_size = 18 * st->scaling;

    st->layers[0].on_update.user = ctx;
    st->layers[0].on_update.callback = _ntCreateDwmContextMain;

    ctx->lpack = _ntGenerateLanguagePack();

    while (ctx->loading_finished != true) {
        // wait 0.1 seconds before checking again
		_ntSetupTimerSync(0.01);
    }

    _ntRendererAddCloseEvent(_ntDwmDestroyContext, ctx, false);

    #if RENDERER_ENABLE_LUA == 1
    register_lua_func(DrawWithFont);
    register_lua_func(LoadFont);
    register_lua_func(GetLocalMousePosition);
    register_lua_func(GetProcesses);
    register_lua_func(GetProcesses1);
    register_lua_func(GetProcessesRaw);
    #endif

    // return context
    return ctx;
}