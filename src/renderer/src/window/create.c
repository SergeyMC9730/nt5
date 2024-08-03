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
#include <nt5emul/renderer_lua_bindings.h>

#include <unistd.h>

#include <pthread.h>

#include <nt5emul/timer.h>

#define register_lua_func(func) lua_register(st->lua_interpreter, #func, _ntRendererLua##func);

void _ntRendererCreateEnvironment() {
	renderer_state_t *st = _ntRendererGetState();

    st->queue = RSBCreateArrayRendererQueue();
#if 0
    st->tweaks = RSBCreateArrayMaxTweak();
#endif
    st->close_events = RSBCreateArrayEvent();

    #if RENDERER_ENABLE_LUA == 1
    st->lua_interpreter = luaL_newstate();
    luaL_openlibs(st->lua_interpreter);

    lua_register(st->lua_interpreter, "DrawText", _ntRendererLuaDrawText);
    lua_register(st->lua_interpreter, "ClearBackground", _ntRendererLuaClearBackground);
    
    register_lua_func(WindowShouldClose);
    register_lua_func(IsWindowReady);
    register_lua_func(IsWindowFullscreen);
    register_lua_func(IsWindowHidden);
    register_lua_func(IsWindowMinimized);
    register_lua_func(IsWindowMaximized);
    register_lua_func(IsWindowFocused);
    register_lua_func(IsWindowResized);

    register_lua_func(ToggleFullscreen);
    register_lua_func(ToggleBorderlessWindowed);
    register_lua_func(MaximizeWindow);
    register_lua_func(MinimizeWindow);
    register_lua_func(RestoreWindow);

    register_lua_func(GetScreenWidth);
    register_lua_func(GetScreenHeight);
    register_lua_func(GetRenderWidth);
    register_lua_func(GetRenderHeight);
    register_lua_func(GetMonitorCount);
    register_lua_func(GetCurrentMonitor);

    register_lua_func(GetMonitorWidth);
    register_lua_func(GetMonitorHeight);
    register_lua_func(GetMonitorPhysicalWidth);
    register_lua_func(GetMonitorPhysicalHeight);
    register_lua_func(GetMonitorRefreshRate);

    // Cursor-related functions
    register_lua_func(ShowCursor);
    register_lua_func(HideCursor);
    register_lua_func(IsCursorHidden);
    register_lua_func(EnableCursor);
    register_lua_func(DisableCursor);
    register_lua_func(IsCursorOnScreen);

    // Drawing-related functions
    register_lua_func(BeginDrawing);
    register_lua_func(EndDrawing);
    register_lua_func(EndMode2D);
    register_lua_func(EndMode3D);
    register_lua_func(EndBlendMode);
    register_lua_func(EndShaderMode);
    register_lua_func(EndTextureMode);
    register_lua_func(EndScissorMode);
    register_lua_func(EndTextureModeStacked);
    register_lua_func(EndVrStereoMode);

    // Timing-related functions
    register_lua_func(SetTargetFPS);
    register_lua_func(GetFrameTime);
    register_lua_func(GetTime);
    register_lua_func(GetFPS);

    // Input-related functions: keyboard
    register_lua_func(IsKeyPressed);
    register_lua_func(IsKeyPressedRepeat);
    register_lua_func(IsKeyDown);
    register_lua_func(IsKeyReleased);
    register_lua_func(IsKeyUp);
    register_lua_func(GetKeyPressed);
    register_lua_func(GetCharPressed);
    register_lua_func(SetExitKey);

    // Input-related functions: mouse
    register_lua_func(IsMouseButtonDown);
    register_lua_func(IsMouseButtonPressed);
    register_lua_func(IsMouseButtonReleased);
    register_lua_func(IsMouseButtonUp);
    register_lua_func(GetMouseX);
    register_lua_func(GetMouseY);
    register_lua_func(SetMouseCursor);
    register_lua_func(GetMousePosition);
    register_lua_func(GetMouseDelta);

    // Basic shapes drawing functions
    register_lua_func(DrawPixel);
    register_lua_func(DrawLine);
    register_lua_func(DrawLineEx);
    register_lua_func(DrawCircle);
    register_lua_func(DrawCircleLines);
    register_lua_func(DrawCircleGradient);
    register_lua_func(DrawEllipse);
    register_lua_func(DrawRectangle);
    register_lua_func(DrawRectangleLines);

    // tools
    register_lua_func(RgbaIntoInt);
    register_lua_func(RgbIntoInt);
    register_lua_func(FloatIntoInt);
    register_lua_func(IntIntoFloat);
    
    #endif

	if (st->thread != 0) {
		_ntRendererCloseEnvironment();
	}

	pthread_create(&st->thread, NULL, _ntRendererThread, NULL);

		// wait for renderer to be ready
	while (!(st->status & RENDERER_READY)) {
		// wait 100 ms before checking again
        _ntSetupTimerSync(0.1);
	}
}

#include <stdio.h>

void _ntRendererCreateEnvironmentEx(bool fake_scaling) {
    renderer_state_t *st = _ntRendererGetState();
    
    st->fake_scaling = fake_scaling;

    printf("st->fake_scaling = %d\n", st->fake_scaling);

    _ntRendererCreateEnvironment();
}