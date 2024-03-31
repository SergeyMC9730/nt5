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

#include <nt5emul/dwm/lua_bindings.h>

#if RENDERER_ENABLE_LUA == 1

#include <raylib.h>

#include <nt5emul/dwm/context.h>
#include <nt5emul/renderer.h>

generate_luafunc(DrawWithFont) {
    int posX = lua_tointeger(L, 1);
    int posY = lua_tointeger(L, 2);
    int rgba = lua_tointeger(L, 3);

    Color col;
    *((int *)&col) = _ntReverseInt(rgba);

    const char *text = lua_tostring(L, 4);
    const char *font_name = lua_tostring(L, 5);

    _ntDwmDrawWithFont(_ntDwmGetGlobal(), (Vector2){(float)posX, (float)posY}, col, text, font_name);

    return 0;
}

generate_luafunc(LoadFont) {
    int xsz = lua_tointeger(L, 1);
    float sp = lua_tonumber(L, 2);
    const char *path = lua_tostring(L, 3);
    const char *font_name = lua_tostring(L, 4);

    _ntDwmLoadFont(_ntDwmGetGlobal(), xsz, sp, path, font_name);

    return 0;
}

generate_luafunc(GetLocalMousePosition) {
    Vector2 v = _ntDwmGetLocalMousePosition(_ntDwmGetGlobal());

    return _ntRendererLuaPushVector2(L, v);
}

generate_luafunc(GetProcesses) {
    rsb_array_Int *values = _ntDwmGetProcesses(_ntDwmGetGlobal());

    lua_createtable(L, values->len, 0);

    for (int i = 0; i < values->len; i++) {
        int val = RSBGetAtIndexInt(values, i);

        lua_pushinteger(L, val);
        lua_rawseti(L, -2, 1 + i);
    }

    RSBDestroyInt(values);

    return 1;
}

generate_luafunc(GetProcesses1) {
    rsb_array_Int *values = _ntDwmGetProcesses1(_ntDwmGetGlobal());

    lua_createtable(L, values->len, 0);

    for (int i = 0; i < values->len; i++) {
        int val = RSBGetAtIndexInt(values, i);

        lua_pushinteger(L, val);
        lua_rawseti(L, -2, 1 + i);
    }

    RSBDestroyInt(values);

    return 1;
}

generate_luafunc(GetProcessesRaw) {
    rsb_array_Int *values = _ntDwmGetProcessesRaw(_ntDwmGetGlobal());

    lua_createtable(L, values->len, 0);

    for (int i = 0; i < values->len; i++) {
        int val = RSBGetAtIndexInt(values, i);

        lua_pushinteger(L, val);
        lua_rawseti(L, -2, 1 + i);
    }

    RSBDestroyInt(values);

    return 1;
}

#endif