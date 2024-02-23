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

// event

typedef struct renderer_event_t {
	void (*callback)(void *user);
	void *user;
} renderer_event_t;

// renderer layer

typedef struct renderer_layer_t {
	renderer_event_t on_draw;
	renderer_event_t on_update;
	void *user;
} renderer_layer_t;

// queue object

typedef struct renderer_queue_object_t {
    renderer_event_t event;
    int fps;
} renderer_queue_object_t;

// value tweak object

#define GEN_TWEAK(tweak) TOIn##tweak, TOOut##tweak, TOInOut##tweak 

typedef enum renderer_tweak_type {
    TOLinear = 0,

    GEN_TWEAK(Sine),
    GEN_TWEAK(Quad),
    GEN_TWEAK(Cubic),
    GEN_TWEAK(Quart),
    GEN_TWEAK(Quint),
    GEN_TWEAK(Expo),
    GEN_TWEAK(Circ),
    GEN_TWEAK(Back),
    GEN_TWEAK(Elastic),
    GEN_TWEAK(Bounce),

    TOEnd
} renderer_tweak_type;

typedef struct renderer_value_tweak_object_t {
    double time;
    double power;
    double passed;

    renderer_tweak_type type;
} renderer_value_tweak_object_t;
typedef struct renderer_float_tweak_object_t {
    renderer_value_tweak_object_t obj;

    float *val;
    float orig;
} renderer_float_tweak_object_t;
typedef struct renderer_double_tweak_object_t {
    renderer_value_tweak_object_t obj;

    double *val;
    double orig;
} renderer_double_tweak_object_t;

typedef enum renderer_tweak_object_type {
    TOTUnknown = 0,
    TOTFloat,
    TOTDouble
} renderer_tweak_object_type;

typedef struct renderer_max_tweak_object_t {
    renderer_float_tweak_object_t _float;
    renderer_double_tweak_object_t _double;
    renderer_tweak_object_type type;
} renderer_max_tweak_object_t;

// arrays

#include <nt5emul/arrays/rsb_array_gen.h>

RSB_ARRAY_DEF_GEN(renderer_queue_object_t, RendererQueue);

RSB_ARRAY_DEF_GEN(renderer_event_t, Event);

#include <raylib.h>

RSB_ARRAY_DEF_GEN(renderer_max_tweak_object_t, MaxTweak);

#include <stdbool.h>

RSB_ARRAY_DEF_GEN(Image, Image);

#include <stdbool.h>

// renderer state

typedef struct renderer_state_t {
#define RENDERER_LAYERS 6
	renderer_layer_t *layers;
	pthread_t thread;
    rsb_array_RendererQueue *queue;
    rsb_array_MaxTweak *tweaks;
    rsb_array_Event *close_events;

#define RENDERER_REQUESTED_STOP 1
#define RENDERER_READY 			2
	unsigned char status;

    // allows renderer to draw fps
    bool draw_fps;

    // scales everything
    float scaling;

    // time since renderer initialization
    double time;
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
// check if function has been runned inside the renderer thread
bool _ntRendererInThread();

// state functions

// get renderer state
renderer_state_t *_ntRendererGetState();

// queue functions

// request function to be called inside the renderer queue.
// requested function is gonna be called on a next frame.
// you can provide userdata for this function as an main argument.
void _ntRendererPushQueue(void (*callback)(void *ctx), void *userdata);

// drawing functions

void _ntRendererDrawStretchedTexture(Texture2D texture, bool x_stretched, bool y_stretched, float xstretchmul, float ysctretchmul, Vector2 pos, Vector2 origin);
void _ntRendererDrawSizedTexture(Texture2D texture, Vector2 size, Vector2 pos, Vector2 origin, bool inside_scale);

// returns centered texture position (not relative!)
Vector2 _ntRendererCenterTexture(Texture2D texture, bool x, bool y);

// load images from .ico file
// original code made by raysan5
//
// additions:
// - dynamic array impl is used instead of raw Image * pointer
// - added support for BMP data
//
// disadvantages:
// - it doesnt work but maybe i will fix this function later
rsb_array_Image *_ntRendererLoadIco(const char *filename, int *count);

// unload images and unload the array itself
void _ntRendererUnloadImages(rsb_array_Image *images);

// process float value
void _ntRendererProcessTweakFloat(renderer_float_tweak_object_t *tweak);
// process double value
void _ntRendererProcessTweakDouble(renderer_double_tweak_object_t *tweak);

// create float value tweak
//
// arguments;
// - `val` - value to be modified
// - `time` - how long it would take for value to fully modify
// - `power` - how much it would modify
// - `type` - easing
void _ntRendererCreateTweakFloat(float *val, double time, double power, renderer_tweak_type type);

// create double value tweak
//
// arguments;
// - `val` - value to be modified
// - `time` - how long it would take for value to fully modify
// - `power` - how much it would modify
// - `type` - easing
void _ntRendererCreateTweakDouble(double *val, double time, double power, renderer_tweak_type type);