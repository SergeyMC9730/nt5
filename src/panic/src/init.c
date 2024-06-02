/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2024  Sergei Baigerov

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

#include "external/glfw/src/internal.h"
#include "raylib.h"

#include <nt5emul/renderer_event.h>
#include <nt5emul/renderer.h>

#include <nt5emul/panic/setup.h>
#include <nt5emul/panic/context.h>

#include <nt5emul/copy_string.h>

#include "nt5emul/tui/environment.h"
#include <nt5emul/tui/text.h>

#include <stdio.h>

int _ntPanicTimeout = 8;
int _ntPanicTimeoutT = 0;

void _ntPanicHangup(void *ptr) {
    _ntPanicTimeoutT++;

    if (_ntPanicTimeoutT >= _ntPanicTimeout) {
        printf("---- SYSTEM IS GOING TO HANG UP ----\n");
        while (true) {}
    }
}

void _ntPanicDraw(struct nt_panic_context *ctx) {
    ClearBackground((Color){0, 0, 170, 255});

    if (ctx == NULL) return;

    _ntTuiDrawText(ctx->error, 0, 0, WHITE);

    _ntRendererPushQueue(_ntPanicHangup, NULL);
}

void _ntPanicSetupDraw(void *ptr) {
    renderer_state_t *st = _ntRendererGetState();

    st->layers[0].on_draw.user = ptr;
    st->layers[0].on_draw.callback = REVENT_CALLBACK_CAST(_ntPanicDraw);
}

void _ntPanicLoadFont(void *ptr) {
    _ntTuiLoadEnvironmentDefault();
    _ntRendererPushQueue(_ntPanicSetupDraw, ptr);

    float scale = GetWindowScaleDPI().x;

    SetTextLineSpacing((int)(8.f * scale));

    _ntRendererSetWindowSize((Vector2){640.f * scale, 480.f * scale});
}

void _ntPanic(const char *error, int error_code) {
    if (error == NULL) {
        printf("-- error: \"error\" is NULL\n");
        return;
    }

    printf("-------- PANIC --------\n  error: %s\n  code: 0x%08X\n", error, error_code);

    struct nt_panic_context *ctx = (struct nt_panic_context *)malloc(sizeof(struct nt_panic_context));
    renderer_state_t *st = _ntRendererGetState();

    if (ctx == NULL) {
        printf("-- error: \"ctx\" is NULL\n");
        return;
    }

    char numbuffer[64] = {0};
    snprintf(numbuffer, 64, "0x%08X", error_code);

    char *_error = (char *)malloc(4096);
    if (_error == NULL) {
        printf("-- error: \"_error\" is NULL\n");
        return;
    }

    ctx->error_code = _ntCopyString(numbuffer);

    snprintf(_error, 4096, "\nA problem has been detected and NT5 has been shut down to prevent damage\nto your computer.\n\n\n%s\n\n"
    "If this is the first time you've seen this Stop error screen,\nrestart your computer. If this scren appears again, follow\nthese "
    "steps\n\nCheck to make sure any new software is properly installed.\nIf this is a new installation, try to update NT5 program.\n\n"
    "If problems continue, disable or remove any newly install software\n. Report this bug in NT5's GitHub repository and wait until the "
    "fix.\n\nTechnical information:\n\n*** STOP: %s",
        error, ctx->error_code
    );
    ctx->error = _error;

    for (int i = 0; i < RENDERER_LAYERS; i++) {
        st->layers[i].on_draw.callback = NULL;
        st->layers[i].on_update.callback = NULL;
    }

    RSBDestroyRendererQueue(st->queue);
    st->queue = RSBCreateArrayRendererQueue();

    _ntRendererPushQueue(_ntPanicLoadFont, ctx);

    return;
}
