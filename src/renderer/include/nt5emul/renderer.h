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

#pragma once

#include <pthread.h>

#pragma pack(push, 1)

typedef struct renderer_layer_t {
	void (*draw)(void *user);
	void (*update)(void *user);
	void *user;
} renderer_layer_t;

#include <stdbool.h>

typedef struct renderer_state_t {
#define RENDERER_LAYERS 4
	renderer_layer_t *layers;
	pthread_t thread;

#define RENDERER_REQUESTED_STOP 1
#define RENDERER_READY 			2
	unsigned char status;
} renderer_state_t;

#pragma pack(pop)

void _ntRendererCreateEnvironment();
void _ntRendererCloseEnvironment();
void _ntRendererUpdate();
void _ntRendererDraw();
void _ntRendererJoin();
void *_ntRendererThread(void *ptr);
renderer_state_t *_ntRendererGetState();