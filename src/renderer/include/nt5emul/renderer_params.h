#pragma once

#define RENDERER_ENABLE_X11_CAPTURE 0

#ifdef HAS_LUA
#define RENDERER_ENABLE_LUA 1
#else
#define RENDERER_ENABLE_LUA 0
#endif