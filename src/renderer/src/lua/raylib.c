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
#include <nt5emul/reverse_int.h>

#if RENDERER_ENABLE_LUA == 1
int _ntRendererLuaDrawText(lua_State *L) {
    const char *text = lua_tostring(L, 1);
    int posX = lua_tointeger(L, 2);
    int posY = lua_tointeger(L, 3);
    int fontSize = lua_tointeger(L, 4);
    int rgba = lua_tointeger(L, 5);

    Color col;
    *((int *)&col) = _ntReverseInt(rgba);

    DrawText(text, posX, posY, fontSize, col);

    return 0;
}
int _ntRendererLuaClearBackground(lua_State *L) {
    int rgba = lua_tointeger(L, 1);

    Color col;
    *((int *)&col) = _ntReverseInt(rgba);

    ClearBackground(col);

    return 0;
}

#define generate_boolvoid(func) int _ntRendererLua##func(lua_State *L) { lua_pushboolean(L, func()); return 1; }
#define generate_voidvoid(func) int _ntRendererLua##func(lua_State *L) { func(); return 0; }
#define generate_intvoid(func) int _ntRendererLua##func(lua_State *L) { lua_pushinteger(L, func()); return 1; }
#define generate_floatvoid(func) int _ntRendererLua##func(lua_State *L) { lua_pushnumber(L, func()); return 1; }
#define generate_doublevoid(func) generate_floatvoid(func)
#define generate_intint(func) int _ntRendererLua##func(lua_State *L) { int val = lua_tointeger(L, 1); lua_pushinteger(L, func(val)); return 1; }
#define generate_voidint(func) int _ntRendererLua##func(lua_State *L) { int val = lua_tointeger(L, 1); func(val); return 0; }
#define generate_boolint(func) int _ntRendererLua##func(lua_State *L) { int val = lua_tointeger(L, 1); lua_pushboolean(L, func(val)); return 1; }

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

generate_voidvoid(ShowCursor);
generate_voidvoid(HideCursor);
generate_boolvoid(IsCursorHidden);
generate_voidvoid(EnableCursor);
generate_voidvoid(DisableCursor);
generate_boolvoid(IsCursorOnScreen);

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

generate_voidint(SetTargetFPS);
generate_floatvoid(GetFrameTime);
generate_doublevoid(GetTime);
generate_intvoid(GetFPS);

generate_boolint(IsKeyPressed);
generate_boolint(IsKeyPressedRepeat);
generate_boolint(IsKeyDown);
generate_boolint(IsKeyReleased);
generate_boolint(IsKeyUp);
generate_intvoid(GetKeyPressed);
generate_intvoid(GetCharPressed);
generate_voidint(SetExitKey);

generate_boolint(IsMouseButtonDown);
generate_boolint(IsMouseButtonPressed);
generate_boolint(IsMouseButtonReleased);
generate_boolint(IsMouseButtonUp);
generate_intvoid(GetMouseX);
generate_intvoid(GetMouseY);
generate_voidint(SetMouseCursor);

int _ntRendererLuaDrawPixel(lua_State *L) {
    int posX = lua_tointeger(L, 1);
    int posY = lua_tointeger(L, 2);
    int rgba = lua_tointeger(L, 3);

    Color col;
    *((int *)&col) = _ntReverseInt(rgba);

    DrawPixel(posX, posY, col);

    return 0;
}

int _ntRendererLuaDrawLine(lua_State *L) {
    int sPosX = lua_tointeger(L, 1);
    int sPosY = lua_tointeger(L, 2);
    int ePosX = lua_tointeger(L, 3);
    int ePosY = lua_tointeger(L, 4);
    int rgba = lua_tointeger(L, 5);

    Color col;
    *((int *)&col) = _ntReverseInt(rgba);

    DrawLine(sPosX, sPosY, ePosX, ePosY, col);

    return 0;
}
int _ntRendererLuaDrawLineEx(lua_State *L) {
    int sPosX = lua_tointeger(L, 1);
    int sPosY = lua_tointeger(L, 2);
    int ePosX = lua_tointeger(L, 3);
    int ePosY = lua_tointeger(L, 4);
    float thick = lua_tonumber(L, 5);
    int rgba = lua_tointeger(L, 6);

    Color col;
    *((int *)&col) = _ntReverseInt(rgba);

    DrawLineEx((Vector2){sPosX, sPosY}, (Vector2){ePosX, ePosY}, thick, col);

    return 0;
}

int _ntRendererLuaDrawCircle(lua_State *L) {
    int centerX = lua_tointeger(L, 1);
    int centerY = lua_tointeger(L, 2);
    float radius = lua_tonumber(L, 3);
    int rgba = lua_tointeger(L, 4);

    Color col;
    *((int *)&col) = _ntReverseInt(rgba);

    DrawCircle(centerX, centerY, radius, col);

    return 0;
}

int _ntRendererLuaDrawCircleLines(lua_State *L) {
    int centerX = lua_tointeger(L, 1);
    int centerY = lua_tointeger(L, 2);
    float radius = lua_tonumber(L, 3);
    int rgba = lua_tointeger(L, 4);

    Color col;
    *((int *)&col) = _ntReverseInt(rgba);

    DrawCircleLines(centerX, centerY, radius, col);

    return 0;
}

int _ntRendererLuaDrawCircleGradient(lua_State *L) {
    int centerX = lua_tointeger(L, 1);
    int centerY = lua_tointeger(L, 2);
    float radius = lua_tonumber(L, 3);
    int rgba1 = lua_tointeger(L, 4);
    int rgba2 = lua_tointeger(L, 5);

    Color col1; *((int *)&col1) = _ntReverseInt(rgba1);
    Color col2; *((int *)&col2) = _ntReverseInt(rgba1);

    DrawCircleGradient(centerX, centerY, radius, col1, col2);

    return 0;
}

int _ntRendererLuaDrawEllipse(lua_State *L) {
    int centerX = lua_tointeger(L, 1);
    int centerY = lua_tointeger(L, 2);
    float radiusH = lua_tonumber(L, 3);
    float radiusV = lua_tonumber(L, 4);
    int rgba = lua_tointeger(L, 5);

    Color col;
    *((int *)&col) = _ntReverseInt(rgba);

    DrawEllipse(centerX, centerY, radiusH, radiusV, col);

    return 0;
}

int _ntRendererLuaDrawRectangle(lua_State *L) {
    int posX = lua_tointeger(L, 1);
    int posY = lua_tointeger(L, 2);
    int width = lua_tointeger(L, 3);
    int height = lua_tointeger(L, 4);
    int rgba = lua_tointeger(L, 5);

    Color col;
    *((int *)&col) = _ntReverseInt(rgba);

    DrawRectangle(posX, posY, width, height, col);

    return 0;
}
int _ntRendererLuaDrawRectangleLines(lua_State *L) {
    int posX = lua_tointeger(L, 1);
    int posY = lua_tointeger(L, 2);
    int width = lua_tointeger(L, 3);
    int height = lua_tointeger(L, 4);
    int rgba = lua_tointeger(L, 5);

    Color col;
    *((int *)&col) = _ntReverseInt(rgba);

    DrawRectangleLines(posX, posY, width, height, col);

    return 0;
}

int _ntRendererLuaGetMousePosition(lua_State *L) {
    return _ntRendererLuaPushVector2(L, GetMousePosition());
}
int _ntRendererLuaGetMouseDelta(lua_State *L) {
    return _ntRendererLuaPushVector2(L, GetMouseDelta());
}

#endif