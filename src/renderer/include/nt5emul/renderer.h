#pragma once

#include <pthread.h>

#pragma pack(push, 1)

typedef struct renderer_layer_t {
	void (*draw)();
	void (*update)();
} renderer_layer_t;

#include <stdbool.h>

typedef struct renderer_state_t {
	renderer_layer_t *layers;
	pthread_t thread;

#define RENDERER_REQUESTED_STOP 1
#define RENDERER_READY 			2
	unsigned char status;
} renderer_state_t;

#pragma pack(pop)

extern renderer_state_t _renderer_state;

void _renderer_create_environment();
void _renderer_close_environment();
void _renderer_update();
void _renderer_draw();
void _renderer_join();