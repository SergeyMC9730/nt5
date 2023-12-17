/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  SergeyMC9730

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

    Contact SergeyMC9730 -- @dogotrigger in Discord
*/

#include <nt5emul/renderer.h>

#include <unistd.h>

#include <pthread.h>

void _ntRendererCreateEnvironment() {
	renderer_state_t *st = _ntRendererGetState();

	if (st->thread != 0) {
		_ntRendererCloseEnvironment();
	}

	pthread_create(&st->thread, NULL, _ntRendererThread, NULL);

		// wait for renderer to be ready
	while (!(st->status & RENDERER_READY)) {
		// wait 0.33 seconds before checking again
		usleep(1000000 / 3);
	}
}