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

#include <unistd.h>

#include <pthread.h>

#include <nt5emul/timer.h>

void _ntRendererCreateEnvironment() {
	renderer_state_t *st = _ntRendererGetState();

    st->queue = RSBCreateArrayRendererQueue();
    st->tweaks = RSBCreateArrayMaxTweak();
    st->close_events = RSBCreateArrayEvent();

    #if RENDERER_ENABLE_LUA == 1
    st->lua_interpreter = luaL_newstate();
    luaL_openlibs(st->lua_interpreter);

    lua_register(st->lua_interpreter, "DrawText", _ntRendererLuaDrawText);
    lua_register(st->lua_interpreter, "ClearBackground", _ntRendererLuaClearBackground);
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