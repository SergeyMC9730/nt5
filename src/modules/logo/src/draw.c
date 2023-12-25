#include <nt5emul/modules/logo/state.h>
#include <nt5emul/version.h>

#ifndef NULL
#define NULL (void *)0
#endif

void logo_draw(void *user) {
    if (_state.old_draw != NULL) _state.old_draw(user);

    int w = GetRenderWidth();
    int h = GetRenderHeight();

    DrawRectangle(0, 0, w, h, BLACK);

    float alignX = (w - _state.logo_texture.width) / 2;
    float alignY = (w - _state.logo_texture.height) / 2;

    DrawTexture(_state.logo_texture, alignX, (int)(alignY * 0.6f), _state.transition_color);

    const char *str = "Powered by raylib";
    int sz = 20;

    Vector2 textsz = MeasureTextEx(GetFontDefault(), str, sz, 1.f);

    DrawText(str, 10, h - textsz.y - 10, sz, _state.transition_color);

    const char *str2 = NT5_VERSION;

    Vector2 textsz2 = MeasureTextEx(GetFontDefault(), str2, sz, 1.f);

    DrawText(str2, w - textsz2.x - 20, h - textsz2.y - 10, sz, _state.transition_color);
}