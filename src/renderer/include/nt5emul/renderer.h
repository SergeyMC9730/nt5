#pragma once

#include <pthread.h>

#pragma pack(push, 1)

typedef struct renderer_layer_t {
	void (*draw)();
	void (*update)();
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