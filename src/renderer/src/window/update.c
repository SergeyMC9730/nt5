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

#include <nt5emul/timer.h>

void _ntRendererUpdate() {
	renderer_state_t *st = _ntRendererGetState();

    st->time += GetFrameTime();

    // process queue list

    for (size_t i = 0; i < st->queue->len; i++) {
        // get object inside the queue
        renderer_queue_object_t *qobj = st->queue->objects + i;

        // run function if it defined
        if (qobj->event.callback != NULL) qobj->event.callback(qobj->event.user);
    }
    
    // process tweaks

    for (size_t i = 0; i < st->tweaks->len; i++) {
        // get object inside the queue
        renderer_max_tweak_object_t *tobj = st->tweaks->objects + i;

        switch(tobj->type) {
            default:
            case TOTFloat: {
                _ntRendererProcessTweakFloat(&tobj->_float);
                break;
            }
            case TOTDouble: {
                _ntRendererProcessTweakDouble(&tobj->_double);
                break;
            }
        }
    }

    // cleanup queue
    while (st->queue->len != 0) {
        RSBPopElementRendererQueue(st->queue);
    }

    // process layers

	for (unsigned short i = 0; i < RENDERER_LAYERS; i++) {
		// update each layer

		if (st->layers[i].on_update.callback != NULL) {
            // update layer if it possible
            st->layers[i].on_update.callback(st->layers[i].on_update.user);
        }
	}
}