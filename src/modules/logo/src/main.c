#include <cterm/applications/api.h>
#include <stdio.h>
#include <nt5emul/renderer.h>
#include <raylib.h>
#include <nt5emul/timer.h>
#include <nt5emul/version.h>

cterm_t *cterm;

Texture2D texture_windows = {};
bool logo_init_complete = false;;
Color logo_color = WHITE;
int frames = 0;

void (*old_draw)(void *user);
void (*old_update)(void *user);

#define OPACITY_ITERATIONS 1

void logo_update(void *user) {
    if (old_update != NULL) old_update(user);

    if (!logo_init_complete) {
        texture_windows = LoadTexture("nt/images/user/ui/mslogo.jpg");
        logo_init_complete = true;
    }

    int frames_per_step = GetFPS() / 60;
    int col_step = 1;
    if (frames_per_step == 0) {
        frames_per_step = 1;
        col_step = 60 / GetFPS();
    }

    int max_val = 0xFF + 1 - col_step;

    printf("a=%02X\n", logo_color.a);

    if ((logo_color.a != max_val && logo_color.a != 0xFF) && !(frames % frames_per_step)) logo_color.a += col_step;

    if (logo_color.a == max_val) {
        logo_color.a = 0xFF;
    }

    frames++;
}

void logo_draw(void *user) {
    if (old_draw != NULL) old_draw(user);

    int w = GetRenderWidth();
    int h = GetRenderHeight();

    // ClearBackground(BLACK);
    DrawRectangle(0, 0, w, h, BLACK);

    float alignX = (w - texture_windows.width) / 2;
    float alignY = (w - texture_windows.height) / 2;

    // printf("r=%d g=%d b=%d a=%d\n", logo_color.r, logo_color.r, logo_color.b, logo_color.a);

    DrawTexture(texture_windows, alignX, (int)(alignY * 0.6f), logo_color);

    const char *str = "Powered by raylib";
    int sz = 20;

    Vector2 textsz = MeasureTextEx(GetFontDefault(), str, sz, 1.f);

    DrawText(str, 10, h - textsz.y - 10, sz, logo_color);

    const char *str2 = NT5_VERSION;

    Vector2 textsz2 = MeasureTextEx(GetFontDefault(), str2, sz, 1.f);

    DrawText(str2, w - textsz2.x - 20, h - textsz2.y - 10, sz, logo_color);
}

void logo_texture_update1() {
    int step = 0xFF / OPACITY_ITERATIONS;

    printf("call %d\n", step);

    logo_color.a -= step;
    // logo_color.a = 0xFF;
}
void logo_texture_update2() {
    renderer_state_t *st = _ntRendererGetState();

    st->layers[RENDERER_LAYERS - 1].draw = old_draw;
    st->layers[RENDERER_LAYERS - 1].update = old_update;

    // SetTargetFPS(GetMonitorRefreshRate(0));

    // UnloadTexture(texture_windows);
    // logo_init_complete = false;
}

bool logo_command(void *data) {
    // SetTargetFPS(15);

    renderer_state_t *st = _ntRendererGetState();

    old_draw = st->layers[RENDERER_LAYERS - 1].draw;
    old_update = st->layers[RENDERER_LAYERS - 1].update;

    st->layers[RENDERER_LAYERS - 1].draw = logo_draw;
    st->layers[RENDERER_LAYERS - 1].update = logo_update;

    // void _ntInstallTimer(void(*callback)(), float seconds);

    logo_color = WHITE;
    logo_color.a = 0;

    float time = 5.f;
    float time_per_step = time / (float)OPACITY_ITERATIONS;

    float tm = 0.f;

    _ntInstallTimer(logo_texture_update2, 5.f);

    // printf("renderer status %d", st->status);

    return true;
}

void init(cterm_t *info) {
    cterm = info;
    
    info->register_command("logo", "Run XP logo animation", false, logo_command);

    return;
}

SET_INFORMATION("logo", "XP Logo", "1.00")