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

#include <pthread.h>

#pragma pack(push, 1)

typedef struct renderer_layer_t {
	void (*draw)(void *user);
	void (*update)(void *user);
	void *user;
} renderer_layer_t;

typedef struct renderer_queue_object_t {
    void (*callback)(void *user);
    void *user;
    int fps;
} renderer_queue_object_t;

#include <nt5emul/arrays/rsb_array_gen.h>

RSB_ARRAY_DEF_GEN(renderer_queue_object_t, RendererQueue);

#include <stdbool.h>

typedef struct renderer_state_t {
#define RENDERER_LAYERS 6
	renderer_layer_t *layers;
	pthread_t thread;
    rsb_array_RendererQueue *queue;

#define RENDERER_REQUESTED_STOP 1
#define RENDERER_READY 			2
	unsigned char status;

    // allows renderer to draw fps
    bool draw_fps;
} renderer_state_t;

#pragma pack(pop)

// environment functions

// creates environment for the renderer
void _ntRendererCreateEnvironment();
// closes the renderer environment
void _ntRendererCloseEnvironment();

// drawing functions

// update layers
void _ntRendererUpdate();

// draw layers
void _ntRendererDraw();

// thread functions

// wait for the renderer thread to exit
void _ntRendererJoin();
// run thread
void *_ntRendererThread(void *ptr);

// state functions

// get renderer state
renderer_state_t *_ntRendererGetState();

// queue functions

// request function to be called inside the renderer queue.
// requested function is gonna be called on a next frame.
// you can provide userdata for this function as an main argument.
void _ntRendererPushQueue(void (*callback)(void *ctx), void *userdata);