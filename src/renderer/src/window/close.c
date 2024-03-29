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

#include <raylib.h>

#include <stdio.h>

void _ntRendererCloseEnvironment() {
	renderer_state_t *st = _ntRendererGetState();

    if (_ntRendererInThread() && st->status & RENDERER_STOPPING) return;

    st->status |= RENDERER_STOPPING;

    for (int i = 0; i < st->close_events->len; i++) {
        renderer_event_t event = RSBGetAtIndexEvent(st->close_events, i);
        
        if (event.callback && !event.user2) event.callback(event.user);
    }

	st->status |= RENDERER_REQUESTED_STOP;

	if (!_ntRendererInThread()) {
        _ntRendererJoin(); // hangs up
    } else {
        CloseWindow();
    }
        
    printf("close the window! 3!!\n");

    RSBDestroyRendererQueue(st->queue);
    RSBDestroyMaxTweak(st->tweaks);

    for (int i = 0; i < st->close_events->len; i++) {
        renderer_event_t event = RSBGetAtIndexEvent(st->close_events, i);
        
        if (event.callback && event.user2) event.callback(event.user);
    }

    RSBDestroyEvent(st->close_events);

	st->status = 0;

    #if RENDERER_ENABLE_LUA == 1
    lua_close(st->lua_interpreter);
    #endif
}