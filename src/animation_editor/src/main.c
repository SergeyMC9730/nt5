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

#include <nt5emul/renderer.h>
#include <nt5emul/dwm/context.h>
#include <nt5emul/tui/environment.h>
#include <stdio.h>
#include <nt5emul/tui/frame.h>
#include <math.h>
#include <nt5emul/arrays/rsb_array_gen.h>
#include <nt5emul/renderer_animation.h>
#include <nt5emul/dwm/button.h>
#include <cterm/cterm.h>
#include <cterm/cterm_command_line.h>

RSB_ARRAY_DEF_GEN(struct renderer_animation, RendererAnimation);
RSB_ARRAY_IMPL_GEN(struct renderer_animation, RendererAnimation);

struct editor_object {
    Rectangle rect;

    rsb_array_RendererAnimation *animations;
};

void displayEditorObject(struct editor_object obj) {
    DrawRectangleRec(obj.rect, RAYWHITE);
    //DrawRectangleLines(obj.rect.x, obj.rect.y, obj.rect.width, obj.rect.height, WHITE);
    // DrawRectangleLinesEx(obj.rect, 2.f, WHITE);
}

RSB_ARRAY_DEF_GEN(struct editor_object, EditorObject);
RSB_ARRAY_IMPL_GEN(struct editor_object, EditorObject);

struct editor_state {
    RenderTexture2D viewpoint;
    Vector2 viewpoint_pos;

    Camera2D cam;

    Vector2 window_size;

    struct Logic {
        Vector2 position; // Position

        Vector2 _internal[4];

        bool movable; // Can move map around with mouse

        bool reverse_accel_x;
        bool reverse_accel_y;
    } cam_logic;

    float cam_zoom;

    rsb_array_EditorObject *objects;

    struct dwm_context *dwm_ctx;

    struct cterm_instance cterm_instance;
};

static struct editor_state __editor_state = {};

float _MapEaseInterpolation(float x) {
    return x == 1.f ? 1.f : 1 - pow(2.f, -10.f * x);
}

bool _CheckFloatAroundValue(float x, float r) {
    return (x > r) || (x < -r);
}


void DrawGrid2D(int sizeWidth, int sizeHeight, int spacing) {
    for (int i = -sizeHeight; i < sizeHeight; i += spacing) {
        DrawLine(-sizeWidth, i, sizeWidth, i, (Color){255, 255, 255, 30});
    }
    for (int i = -sizeWidth; i < sizeWidth; i += spacing) {
        DrawLine(i, -sizeHeight, i, sizeHeight, (Color){255, 255, 255, 30});
    }
}

Rectangle getVisibleCameraArea() {
    int offscreen = 25;

    Rectangle r = {__editor_state.cam.target.x - offscreen, __editor_state.cam.target.y - offscreen};

    r.width = __editor_state.viewpoint.texture.width / __editor_state.cam.zoom + (offscreen * 2);
    r.height = __editor_state.viewpoint.texture.height / __editor_state.cam.zoom + (offscreen * 2);

    return r;
}

void drawViewpoint() {
    if (__editor_state.cam_logic.movable) {
        float delta = GetFrameTime();

        Vector2 future_position = __editor_state.cam_logic.position;
        future_position.x += __editor_state.cam_logic._internal[1].x;
        future_position.y += __editor_state.cam_logic._internal[1].y;

        Vector2 v1;
        v1.x = future_position.x;
        v1.y = future_position.y;

        v1.x -= __editor_state.cam_logic._internal[1].x;
        v1.y -= __editor_state.cam_logic._internal[1].y;

        __editor_state.cam_logic._internal[0] = GetMousePosition();

        float accel_x = __editor_state.cam_logic._internal[1].x;
        float accel_y = __editor_state.cam_logic._internal[1].y;

        if (__editor_state.cam_logic.reverse_accel_x) {
            accel_x = -accel_x;
        }
        if (__editor_state.cam_logic.reverse_accel_y) {
            accel_y = -accel_y;
        }

        __editor_state.cam_logic.position.x += accel_x / __editor_state.cam.zoom; // velocity x
        __editor_state.cam_logic.position.y += accel_y / __editor_state.cam.zoom; // velocity y
    
        bool is_negative_velocity_x = false;
        bool is_negative_velocity_y = false;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {   
            Rectangle r1;

            r1.width = __editor_state.viewpoint.texture.width;
            r1.height = __editor_state.viewpoint.texture.height;
            r1.x = __editor_state.viewpoint_pos.x;
            r1.y = __editor_state.viewpoint_pos.y;

            if (CheckCollisionPointRec(__editor_state.cam_logic._internal[0], r1)) {
                __editor_state.cam_logic._internal[1] = GetMouseDelta();

                // __editor_state.cam_logic._internal[1].x *= delta * 100.f;
                // __editor_state.cam_logic._internal[1].y *= delta * 100.f;

                __editor_state.cam_logic._internal[3].x = __editor_state.cam_logic._internal[1].x < 0.f;
                __editor_state.cam_logic._internal[3].y = __editor_state.cam_logic._internal[1].y < 0.f;

                __editor_state.cam_logic._internal[2].x = 1.f;
                __editor_state.cam_logic._internal[2].y = 1.f;
            }
        } else {
            if ((_CheckFloatAroundValue(__editor_state.cam_logic._internal[1].x, 0.f) || _CheckFloatAroundValue(__editor_state.cam_logic._internal[1].y, 0.f)) && __editor_state.cam_logic._internal[2].y >= 1.f) {

                float interpolation = _MapEaseInterpolation(__editor_state.cam_logic._internal[2].x) * delta * 5.5f;

                float max_time = 30.f;

                __editor_state.cam_logic._internal[2].x -= delta / max_time;

                if (__editor_state.cam_logic._internal[3].x >= 1.f) {
                    if (__editor_state.cam_logic._internal[1].x <= 0.f) __editor_state.cam_logic._internal[1].x += interpolation; 
                    else __editor_state.cam_logic._internal[1].x = 0.f;
                } else {
                    if (__editor_state.cam_logic._internal[1].x >= 0.f) __editor_state.cam_logic._internal[1].x -= interpolation;
                    else __editor_state.cam_logic._internal[1].x = 0.f; 
                }
                if (__editor_state.cam_logic._internal[3].y >= 1.f) {
                    if (__editor_state.cam_logic._internal[1].y <= 0.f) __editor_state.cam_logic._internal[1].y += interpolation;
                    else __editor_state.cam_logic._internal[1].y = 0.f;   
                } else {
                    if (__editor_state.cam_logic._internal[1].y >= 0.f) __editor_state.cam_logic._internal[1].y -= interpolation;
                    else __editor_state.cam_logic._internal[1].y = 0.f;
                }

                float old_velx = __editor_state.cam_logic._internal[1].x;
                float old_vely = __editor_state.cam_logic._internal[1].y;

                __editor_state.cam_logic._internal[1].x = fabs(__editor_state.cam_logic._internal[1].x);
                __editor_state.cam_logic._internal[1].y = fabs(__editor_state.cam_logic._internal[1].y);

                if (__editor_state.cam_logic._internal[1].x == interpolation) {
                    __editor_state.cam_logic._internal[1].x = 0.f;
                } else {
                    __editor_state.cam_logic._internal[1].x = old_velx;
                }

                if (__editor_state.cam_logic._internal[1].y == interpolation) {
                    __editor_state.cam_logic._internal[1].y = 0.f;
                } else {
                    __editor_state.cam_logic._internal[1].y = old_vely;
                }

                if ((__editor_state.cam_logic._internal[1].x == 0.f) && (__editor_state.cam_logic._internal[1].y == 0.f)) __editor_state.cam_logic._internal[2].x = 0.f; // stop moving

                // printf("vx %f vy %f time %f i %f | vx_neg %d vy_neg %d\n", 
                //     __editor_state.cam_logic._internal[1].x, __editor_state.cam_logic._internal[1].y, __editor_state.cam_logic._internal[2].x, interpolation,
                //     (int)__editor_state.cam_logic._internal[3].x, (int)__editor_state.cam_logic._internal[3].y
                // );

                if (__editor_state.cam_logic._internal[2].x <= 0.f) __editor_state.cam_logic._internal[2].y = 0.f;
            } else {
                __editor_state.cam_logic._internal[1].x = 0.f;
                __editor_state.cam_logic._internal[1].y = 0.f;
            }
        }
    }

    __editor_state.cam.rotation = 0.f;
    __editor_state.cam.offset = (Vector2){0, 0};
    __editor_state.cam.target = __editor_state.cam_logic.position;

    BeginTextureModeStacked(__editor_state.viewpoint);
    BeginMode2D(__editor_state.cam);

    ClearBackground((Color){30, 30, 30, 255});

    int limit = 100000 / 2;
    int limit_y = limit / 20;

    int spacing = 20;
    float text_size = 8.f;
    float text_spacing = 1.f;
    int line_length = 5;

    if (__editor_state.cam_zoom < 1.f) {
        spacing = 40;
        text_size = 10.f;
    }
    if (__editor_state.cam_zoom < 0.5f) {
        spacing = 70;
        text_size = 15.f;
    }
    if (__editor_state.cam_zoom >= 3.f) {
        spacing = 10;
        text_size = 4.f;
    }
    if (__editor_state.cam_zoom >= 9.f) {
        spacing = 5;
        text_size = 2.f;
        text_spacing = 0.5f;
        line_length = 2;
    }

    Rectangle view_area = getVisibleCameraArea();

    char buf[64] = {0};

    DrawLine(-limit, 0, limit, 0, GRAY);

    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);

    for (int i = -limit; i < limit; i += spacing) {
        if (CheckCollisionPointRec((Vector2){i, 0}, view_area)) {
            DrawLine(i, line_length, i, -line_length, GRAY);

            if (i != 0) {
                snprintf(buf, 64, "%d", i);
                DrawTextPro(GetFontDefault(), buf, (Vector2){i, line_length + 1}, (Vector2){}, 45.f, text_size, text_spacing, (Color){255, 255, 255, 64});
            }
        }
    }

    DrawLine(0, -limit_y, 0, limit_y, GRAY);

    for (int i = -limit_y; i < limit_y; i += spacing) {
        if (CheckCollisionPointRec((Vector2){0, i}, view_area)) {
            DrawLine(-line_length, i, line_length, i, GRAY);

            if (i != 0) {
                snprintf(buf, 64, "%d", i);
                DrawTextPro(GetFontDefault(), buf, (Vector2){line_length + 1, i}, (Vector2){}, 0.f, text_size, text_spacing, (Color){255, 255, 255, 64});
            }
        }
    }

    DrawGrid2D(limit, limit_y, 20);

    for (int i = 0; i < __editor_state.objects->len; i++) {
        struct editor_object obj = RSBGetAtIndexEditorObject(__editor_state.objects, i);
    
        displayEditorObject(obj);
    }

    EndMode2D();

    EndTextureModeStacked();
}

void draw(void *ctx) {
    renderer_state_t *st = _ntRendererGetState();

    __editor_state.cam.zoom = st->scaling + __editor_state.cam_zoom;

    // printf("zoom=%f\n", __editor_state.cam.zoom);

    drawViewpoint();

    struct nt_tui_environment *st_tui = _ntGetTuiEnvironment();

    int w = st->current_window_size.x / st_tui->base_font_size.x - 1;
    int h = (st->current_window_size.y / st_tui->base_font_size.y) - 7;

    Rectangle rect = {0, 0, w, h};
    Rectangle real_rect = rect;

    real_rect.width *= st_tui->base_font_size.x;
    real_rect.height *= st_tui->base_font_size.y;

    Rectangle gradientRect = {0, __editor_state.viewpoint.texture.height, st->current_window_size.x, st->current_window_size.y - __editor_state.viewpoint.texture.height};
    Rectangle baseRect = {0, 0, gradientRect.width, gradientRect.y};

    Color bg = (Color){30, 30, 30, 255};

    DrawRectangleRec(baseRect, bg);
    DrawRectangleGradientV(gradientRect.x, gradientRect.y, gradientRect.width, gradientRect.height, bg, BLACK);

    _ntRendererDrawSizedTexture(__editor_state.viewpoint.texture, (Vector2){1.f, -1.f}, __editor_state.viewpoint_pos, (Vector2){}, true);

    char buf[64] = {0};
    snprintf(buf, 64, "Viewpoint\n%d FPS\nZoom: %f", GetFPS(), __editor_state.cam_zoom + 1.f);

    _ntTuiDrawFrame(rect, WHITE, buf);

    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_BILINEAR);

    if (__editor_state.dwm_ctx != NULL) {
        {
            struct dwm_button btn = {};
            btn.button = (Rectangle){gradientRect.x + (7 * st->scaling) , gradientRect.y + (15* st->scaling), (100 * st->scaling), (25 * st->scaling)};
            btn.howered.ability = true;
            btn.activated.ability = true;
            btn.text = "New Object";

            bool state = _ntDwmDrawButton(__editor_state.dwm_ctx, &btn);
        
            if (state) {
                printf("clicked 1\n");

                Rectangle view_area = getVisibleCameraArea();

                struct editor_object obj;
                obj.animations = RSBCreateArrayRendererAnimation();
                obj.rect = (Rectangle){0, 0, 10, 10};

                RSBAddElementEditorObject(__editor_state.objects, obj);

                struct cterm_execute_result r;
		        _ctermExecute(&__editor_state.cterm_instance, "notify \"     Created new object", &r);
            }
        }

        {
            struct dwm_button btn = {};
            btn.button = (Rectangle){gradientRect.x + (7 * st->scaling), gradientRect.y + (45 * st->scaling), (100 * st->scaling), (25 * st->scaling)};
            btn.howered.ability = true;
            btn.activated.ability = true;
            btn.text = "Save";

            bool state = _ntDwmDrawButton(__editor_state.dwm_ctx, &btn);

            if (state) {
                printf("clicked 2\n");
            }
        }
    }
}

void checkWindowSz() {
    renderer_state_t *st = _ntRendererGetState();
    struct nt_tui_environment *st_tui = _ntGetTuiEnvironment();

    int w = (st->current_window_size.x / st_tui->base_font_size.x - 1) * st_tui->base_font_size.x;
    int h = ((st->current_window_size.y / st_tui->base_font_size.y) - 7) * st_tui->base_font_size.y;

    if ((w != __editor_state.viewpoint.texture.width) || (h != __editor_state.viewpoint.texture.height)) {
        // printf("reloading viewpoint\n");

        UnloadRenderTexture(__editor_state.viewpoint);
        __editor_state.viewpoint = LoadRenderTexture(w, h);
    }
}

void update(void *ctx) {
    float wheel = GetMouseWheelMove();

    if (wheel != 0.f) {
        if (wheel < 0.f && __editor_state.cam_zoom >= -0.5) {
            __editor_state.cam_zoom += wheel / 8.f;
        }
        if (wheel > 0.f) {
            __editor_state.cam_zoom += wheel / 8.f;
        }
    }

    checkWindowSz();
}

void rendererThreadInit(void *ctx) {
    renderer_state_t *st = _ntRendererGetState();
    struct nt_tui_environment *st_tui = _ntGetTuiEnvironment();

    // _ntRendererSetDpiScale(2.f);

    SetWindowMinSize(640 * st->scaling, 480 * st->scaling);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    _ntTuiLoadEnvironmentDefault(st->scaling);

    int w = st->current_window_size.x / st_tui->base_font_size.x - 1;
    int h = (st->current_window_size.y / st_tui->base_font_size.y) - 7;

    Rectangle rect = {0, 0, w, h};

    rect.width *= st_tui->base_font_size.x;
    rect.height *= st_tui->base_font_size.y;

    __editor_state.viewpoint = LoadRenderTexture(rect.width, rect.height);
    __editor_state.cam_logic.position.x = -__editor_state.viewpoint.texture.width / 2;
    __editor_state.cam_logic.position.y = -__editor_state.viewpoint.texture.height / 2;

    st->layers[0].on_draw.callback = draw;
    st->layers[0].on_update.callback = update;

    _ntRendererSetFPS(GetMonitorRefreshRate(0));
}

void setupFontData(void *ctx) {
    struct dwm_context_font *font = _ntDwmGetFontRef(__editor_state.dwm_ctx, "tahomabd8");
    renderer_state_t *st = _ntRendererGetState();

    if (font != NULL) {
        font->real_size = 18 * st->scaling;
        font->spacing = 1;
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("Animation file not specified. Creating new project\n");
    }

    __editor_state.cam_logic.movable = true;
    __editor_state.cam_logic.reverse_accel_x = true;
    __editor_state.cam_logic.reverse_accel_y = true;

    __editor_state.objects = RSBCreateArrayEditorObject();

    // init NT renderer
    _ntRendererModifyPreinitOptions(true, true);
	_ntRendererCreateEnvironment();

    _ntRendererPushQueue(rendererThreadInit, NULL);

    __editor_state.dwm_ctx = _ntDwmCreateContext("ntresources/basic.theme");
    _ntDwmSetGlobal(__editor_state.dwm_ctx);

    _ntRendererPushQueue(setupFontData, NULL);

    __editor_state.cterm_instance = _ctermInit(true);
    __editor_state.cterm_instance.command_line.output = stdout;

    _ntRendererJoin();

    return 0;
}