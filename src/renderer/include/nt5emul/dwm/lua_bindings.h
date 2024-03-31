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

// lua bindings
#if RENDERER_ENABLE_LUA == 1

#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#define generate_luafunc(func) int _ntDwmLua##func(lua_State *L)

generate_luafunc(DrawWithFont);
generate_luafunc(LoadFont);
generate_luafunc(GetLocalMousePosition);
generate_luafunc(GetProcesses);
generate_luafunc(GetProcesses1);
generate_luafunc(GetProcessesRaw);

#endif