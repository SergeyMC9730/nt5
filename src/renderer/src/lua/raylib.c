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

#if RENDERER_ENABLE_LUA == 1
int _ntRendererLuaDrawText(lua_State *L) {
    const char *text = lua_tostring(L, 1);
    int posX = lua_tointeger(L, 2);
    int posY = lua_tointeger(L, 3);
    int fontSize = lua_tointeger(L, 4);
    int rgba = lua_tointeger(L, 5);

    Color col;
    *((int *)&col) = rgba;

    DrawText(text, posX, posY, fontSize, col);

    return 0;
}
int _ntRendererLuaClearBackground(lua_State *L) {
    int rgba = lua_tointeger(L, 1);

    Color col;
    *((int *)&col) = rgba;

    ClearBackground(col);

    return 0;
}
#endif