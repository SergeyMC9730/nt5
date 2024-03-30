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

#include <nt5emul/renderer_params.h>
#include <raylib.h>

// lua bindings
#if RENDERER_ENABLE_LUA == 1

#define generate_luafunc(func) int _ntRendererLua##func(lua_State *L)
#define generate_boolvoid(func) generate_luafunc(func)
#define generate_voidvoid(func) generate_luafunc(func)
#define generate_intvoid(func) generate_luafunc(func)
#define generate_intint(func) generate_luafunc(func)
#define generate_voidint(func) generate_luafunc(func)
#define generate_floatvoid(func) generate_luafunc(func)
#define generate_doublevoid(func) generate_luafunc(func)
#define generate_boolint(func) generate_luafunc(func)

// Window-related functions
generate_boolvoid(WindowShouldClose);
generate_boolvoid(IsWindowReady);
generate_boolvoid(IsWindowFullscreen);
generate_boolvoid(IsWindowHidden);
generate_boolvoid(IsWindowMinimized);
generate_boolvoid(IsWindowMaximized);
generate_boolvoid(IsWindowFocused);
generate_boolvoid(IsWindowResized);

generate_voidvoid(ToggleFullscreen);
generate_voidvoid(ToggleBorderlessWindowed);
generate_voidvoid(MaximizeWindow);
generate_voidvoid(MinimizeWindow);
generate_voidvoid(RestoreWindow);

generate_intvoid(GetScreenWidth);
generate_intvoid(GetScreenHeight);
generate_intvoid(GetRenderWidth);
generate_intvoid(GetRenderHeight);
generate_intvoid(GetMonitorCount);
generate_intvoid(GetCurrentMonitor);

generate_intint(GetMonitorWidth);
generate_intint(GetMonitorHeight);
generate_intint(GetMonitorPhysicalWidth);
generate_intint(GetMonitorPhysicalHeight);
generate_intint(GetMonitorRefreshRate);

// Cursor-related functions
generate_voidvoid(ShowCursor);
generate_voidvoid(HideCursor);
generate_boolvoid(IsCursorHidden);
generate_voidvoid(EnableCursor);
generate_voidvoid(DisableCursor);
generate_boolvoid(IsCursorOnScreen);

// Drawing-related functions
generate_voidvoid(BeginDrawing);
generate_voidvoid(EndDrawing);
generate_voidvoid(EndMode2D);
generate_voidvoid(EndMode3D);
generate_voidvoid(EndBlendMode);
generate_voidvoid(EndShaderMode);
generate_voidvoid(EndTextureMode);
generate_voidvoid(EndScissorMode);
generate_voidvoid(EndTextureModeStacked);
generate_voidvoid(EndVrStereoMode);

// Timing-related functions
generate_voidint(SetTargetFPS);
generate_floatvoid(GetFrameTime);
generate_doublevoid(GetTime);
generate_intvoid(GetFPS);

// Input-related functions: keyboard
generate_boolint(IsKeyPressed);
generate_boolint(IsKeyPressedRepeat);
generate_boolint(IsKeyDown);
generate_boolint(IsKeyReleased);
generate_boolint(IsKeyUp);
generate_intvoid(GetKeyPressed);
generate_intvoid(GetCharPressed);
generate_voidint(SetExitKey);

// Input-related functions: mouse
generate_boolint(IsMouseButtonDown);
generate_boolint(IsMouseButtonPressed);
generate_boolint(IsMouseButtonReleased);
generate_boolint(IsMouseButtonUp);
generate_intvoid(GetMouseX);
generate_intvoid(GetMouseY);
generate_voidint(SetMouseCursor);
generate_voidint(GetMousePosition);
generate_voidint(GetMouseDelta);

// Basic shapes drawing functions
generate_luafunc(DrawPixel);
generate_luafunc(DrawLine);
generate_luafunc(DrawLineEx);
generate_luafunc(DrawPixelEx);
generate_luafunc(DrawCircle);
generate_luafunc(DrawCircleLines);
generate_luafunc(DrawCircleGradient);
generate_luafunc(DrawEllipse);
generate_luafunc(DrawRectangle);
generate_luafunc(DrawRectangleLines);

generate_luafunc(DrawText);
generate_luafunc(ClearBackground);

#undef generate_luafunc

#endif