#pragma once

#include "basic_theme.h"

int _ntParseDwmTheme(void *user, const char *section, const char *name, const char *value);

struct dwm_theme {
    struct dwm_basic_theme basic;
};