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

int _ntRendererLuaRgbaIntoInt(lua_State *L) {
    int r = lua_tointeger(L, 1);
    int g = lua_tointeger(L, 2);
    int b = lua_tointeger(L, 3);
    int a = lua_tointeger(L, 4);

    Color col = {r, g, b, a};
    int rep = *((int *)&col);

    lua_pushinteger(L, rep);

    return 1;
}
int _ntRendererLuaRgbIntoInt(lua_State *L) {
    int r = lua_tointeger(L, 1);
    int g = lua_tointeger(L, 2);
    int b = lua_tointeger(L, 3);
    int a = 255;

    Color col = {r, g, b, a};
    int rep = *((int *)&col);

    lua_pushinteger(L, rep);

    return 1;
}

/*
generate_luafunc(FloatIntoInt);
generate_luafunc(IntIntoFloat);
*/

int _ntRendererLuaFloatIntoInt(lua_State *L) {
    float v = lua_tonumber(L, 1);

    lua_pushinteger(L, (int)v);

    return 1;
}
int _ntRendererLuaIntIntoFloat(lua_State *L) {
    float v = (float)lua_tointeger(L, 1);

    lua_pushnumber(L, v);

    return 1;
}

#endif
