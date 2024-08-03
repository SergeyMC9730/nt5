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

#include "nt5emul/renderer_event.h"
#include <nt5emul/modules/explorer/state.h>
#include <nt5emul/modules/explorer/shell.h>
#include <nt5emul/renderer.h>
#include <nt5emul/dwm/window.h>
#include <nt5emul/dwm/context.h>
#include <nt5emul/dwm/button.h>
#include <nt5emul/timer.h>
#include <nt5emul/version.h>
#include <nt5emul/renderer_keyframe.h>

#include <stdio.h>

void explorer_shell_mouse_reset(void *ctx) {
    _state.icon_pressed_times = 0;
}

void explorer_window_created(struct dwm_window *wnd) {
    printf("EXPLORER window created %d\n", wnd->process.pid);

    struct renderer_animation *free_anim = NULL;

    for (int i = 0; i < STATE_ARRAYS_LEN; i++){
        if (_state.animations[i].anim_id == -1) {
            free_anim = _state.animations + i;

            if (free_anim->keyframes != NULL) {
                free(free_anim->keyframes);
                free_anim->keyframes = NULL;
            }

            break;
        }
    }

    if (!free_anim) {
        printf("free_anim cannot be found (pid=%d)\n", wnd->process.pid);

        return;
    }

    struct renderer_keyframe *frame = (struct renderer_keyframe *)calloc(1, sizeof(struct renderer_keyframe));

    renderer_state_t *st = _ntRendererGetState();

    frame->easing = TOOutExpo;
    frame->length = 0.5;
    frame->ending_value = (double)50 * (double)st->scaling;

    free_anim->anim_id = wnd->process.pid;
    free_anim->count = 1;
    free_anim->keyframes = frame;

    free_anim->starting_value = 1;
    free_anim->itime = 0;
    free_anim->time = 0;
    free_anim->current_value = free_anim->starting_value;
    free_anim->current_keyframe = 0;
    free_anim->delta = (double)1 / (double)st->expected_fps;

    if (!free_anim) return;
}

void explorer_window_closed(struct dwm_window *wnd) {
    printf("EXPLORER window closed %d\n", wnd->process.pid);

    struct renderer_animation *anim = NULL;

    for (int i = 0; i < STATE_ARRAYS_LEN; i++){
        if (_state.animations[i].anim_id == wnd->process.pid) {
            anim = _state.animations + i;

            if (anim->keyframes != NULL) {
                free(anim->keyframes);
                anim->keyframes = NULL;
            }

            anim->anim_id = -1;

            return;
        }
    }
}


void explorer_shell_init() {
    struct dwm_context *dctx = _ntDwmGetGlobal();

    renderer_event_t ev;
    ev.callback = REVENT_CALLBACK_CAST(explorer_window_created);

    renderer_event_t ev2;
    ev2.callback = REVENT_CALLBACK_CAST(explorer_window_closed);

    RSBAddElementEvent(dctx->window_create_event, ev);
    RSBAddElementEvent(dctx->window_close_event, ev2);

    for (int i = 0; i < STATE_ARRAYS_LEN; i++){
        _state.animations[i].anim_id = -1;
    }
}

bool explorer_pressed_on_window() {
    struct dwm_context *dctx = _ntDwmGetGlobal();
    renderer_state_t *st = _ntRendererGetState();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        rsb_array_Int *pids = _ntDwmGetProcesses(dctx);

        bool window_selected = false;

        for (int i = 0; i < pids->len; i++) {
            struct dwm_window *_wnd = _ntDwmGetProcess(dctx, RSBGetAtIndexInt(pids, i));

            if (_wnd->hidden.state) continue;

            Rectangle sz = {
                _wnd->position.x, _wnd->position.y,
                _wnd->size.x * st->scaling, _wnd->size.y * st->scaling
            };

            if (CheckCollisionPointRec(GetMousePosition(), sz)) {
                window_selected = true;
                break;
            }
        }

        RSBDestroyInt(pids);

        if (window_selected) return true;
    }

    return false;
}

#include <cterm/cterm.h>
#include <cterm/cterm_command_line.h>

void explorer_shell_draw_icons() {
    renderer_state_t *st = _ntRendererGetState();

    Vector2 start_pos = {
        27 * st->scaling, 6 * st->scaling
    };

    Vector2 current_pos = start_pos;

    int ix = 0;
    int iy = 0;

    bool clicked_icon = false;
    int old_id = _state.icon_pressed_id;

    for (int i = 0; i < 8; i++) {
        if (_state.icons[i].width == 0) continue;

        Color col = WHITE;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !explorer_pressed_on_window()) {
            if (
                CheckCollisionPointRec(
                    GetMousePosition(),
                    (Rectangle){
                        current_pos.x, current_pos.y, _state.icons[i].width * st->scaling, _state.icons[i].height * st->scaling
                    }
                )
            )
            {
                _state.icon_pressed_id = i;
                clicked_icon = true;
            }

            _ntInstallTimer(explorer_shell_mouse_reset, 0.5f, NULL);
        }

        if (clicked_icon || _state.icon_pressed_id == i) {
            col = BLUE;
        }

        DrawTextureEx(_state.icons[i], current_pos, 0.f, st->scaling, col);

        ix++;

        if (ix == 2) {
            ix = 0;
            iy++;
        }

        current_pos.x = start_pos.x + ix * _state.icons[i].width + (56 * ix * st->scaling);
        current_pos.y = start_pos.y + (iy * _state.icons[i].height) + (32 * iy * st->scaling);
    }

    if (clicked_icon) {
        _state.icon_pressed_times++;

        if (old_id != _state.icon_pressed_id) {
            _state.icon_pressed_times = 1;
        }

        if (_state.icon_pressed_times == 2) {
            _state.icon_pressed_times = 1;

            const char *cmd_name = explorer_map_icon(_state.icon_pressed_id);

            struct cterm_execute_result r;
            _ctermExecute(_state.runtime, cmd_name, &r);

            if (r.command_not_found) {
                _ctermExecute(_state.runtime, "notify Selected command doesn't exist", &r);
            }
        }
    }
}

int explorer_shell_draw_start(Rectangle taskbar) {
    renderer_state_t *st = _ntRendererGetState();

    struct dwm_button btn = {};

    btn.text =  _state.cterm_shell_start_classic;
    btn.button.x = 2 * st->scaling;
    btn.button.y = taskbar.y + (0 * st->scaling);
    btn.button.width = 56 * st->scaling;
    btn.button.height = 22 * st->scaling;

    btn.howered.ability = true;
    btn.activated.ability = true;

    struct dwm_context *dctx = _ntDwmGetGlobal();

    if (_ntDrawDWMButton(dctx, &btn)) {
        struct cterm_execute_result r;

        _ctermExecute(_state.runtime, "notify Not implemented yet!\nRunning explorer", &r);
        _ctermExecute(_state.runtime, "explorer", &r);
    }

    return btn.button.x + btn.button.width + (1 * st->scaling);
}

void explorer_shell_draw_watermark(Vector2 offset) {
    Color col = WHITE;
    col.a = 128;

    _ntRendererDrawWatermarkEx(offset, col);
}

Rectangle explorer_shell_draw_taskbar(void *ctx) {
    renderer_state_t *st = _ntRendererGetState();

    Vector2 sz = {
        st->current_window_size.x,
        st->current_window_size.y
    };

    struct dwm_context *dctx = _ntDwmGetGlobal();

    Color border1 = dctx->theme.basic.active_border_color;
    Color border2 = dctx->theme.basic.window_base_color;

    Rectangle taskbar = {
        .x = 0,
        .y = sz.y - (26 * st->scaling),
        .height = 26 * st->scaling,
        .width = sz.x
    };

    DrawRectanglePro(taskbar, (Vector2){}, 0.f, border1);

    taskbar.y++;
    DrawLine(taskbar.x, taskbar.y, taskbar.x + taskbar.width,  taskbar.y, border2);

    taskbar.y++;

    int offset = explorer_shell_draw_start(taskbar) + (4 * st->scaling);

    int btn_x = taskbar.x + offset;
    int btn_xsz = 50 * st->scaling;

    rsb_array_Int *pids = _ntDwmGetProcesses1(dctx);

    for (int i = 0; i < pids->len; i++) {
        struct dwm_window *_wnd = _ntDwmGetProcess(dctx, RSBGetAtIndexInt(pids, i));

        struct dwm_button btn = {};
        btn.text = _wnd->title;
        btn.button.x = btn_x;
        btn.button.y = taskbar.y;
        btn.button.width = btn_xsz;
        btn.button.height = taskbar.height - (4 * st->scaling);

        struct renderer_animation *window_anim = NULL;

        for (int i = 0; i < STATE_ARRAYS_LEN; i++){
            if (_state.animations[i].anim_id == _wnd->process.pid) {
                window_anim = _state.animations + i;

                break;
            }
        }

        if (window_anim) {
            btn.button.width = window_anim->current_value;
        }

        btn.howered.ability = true;
        btn.activated.ability = true;

        if (_wnd->hidden.state) {
            btn.dark.ability = true;
            btn.dark.state = true;
        }

        if (dctx->selected_window == _wnd) {
            btn.howered.ability = false;
            btn.howered.state = true;
            btn.dark.ability = true;
            btn.dark.state = true;
        }

        if (_ntDrawDWMButton(dctx, &btn)) {
            dctx->selected_window = _wnd;
            _wnd->hidden.state = false;
        }

        btn_x += btn.button.width + (4 * st->scaling);
    }

    RSBDestroyInt(pids);

    return taskbar;
}

void explorer_shell_draw_background(void *ctx) {
    renderer_state_t *st = _ntRendererGetState();

    Vector2 sz = {
        st->current_window_size.x,
        st->current_window_size.y
    };

    float ratio = 1.f;

    if ((float)_state.background.height > sz.y) {
        ratio = sz.y / (float)_state.background.height;
    }

    if (((float)_state.background.width * ratio) < sz.x) {
        ratio = sz.x / (float)_state.background.width;
    }

    int posX = (sz.x - ((float)_state.background.width * ratio)) / 2;
    int posY = (sz.y - ((float)_state.background.height * ratio)) / 2;

    _ntRendererDrawSizedTexture(_state.background, (Vector2){ratio, ratio}, (Vector2){posX, posY}, (Vector2){}, false);
}

void explorer_shell_draw(void *ctx) {
    explorer_shell_draw_background(ctx);
    Rectangle taskbar = explorer_shell_draw_taskbar(ctx);
    explorer_shell_draw_icons();
    explorer_shell_draw_watermark((Vector2){0, -taskbar.height});

    if (_state.old_layer.on_draw.callback) _state.old_layer.on_draw.callback(_state.old_layer.on_draw.user);
}

#include <string.h>

#include <nt5emul/modules/explorer/intro.h>

void *explorer_shell_test_animation1_thread(void *user) {
    for (int i = 0; i < 256 * 1.5; i++) {
        explorer_intro_create();

        // _ntSetupTimerSync(0.05f);
    }

    return NULL;
}
void explorer_shell_test_animation1() {
    pthread_t thr;

    pthread_create(&thr, NULL, explorer_shell_test_animation1_thread, NULL);
}

void explorer_shell_update(void *ctx) {
    if (_state.background.width == 0) {
        _state.background = LoadTexture("nt/images/user/wallpapers/bliss.jpg");

        SetWindowState(FLAG_WINDOW_RESIZABLE);

        Sound snd = LoadSound("nt/sounds/xpstartu.wav");
        PlaySound(snd);

        // int count = 0;
        // rsb_array_Image *img100 = _ntRendererLoadIco("ntresources/ext/reactos/explorer/100.ico", &count);

        // printf("-----_ COUNT: %d\n", count);

        // _ntRendererUnloadImages(img100);

        for (int i = 0; i < 8; i++) {
            const char *cmd_name = explorer_map_icon(i);

            // if (strcmp(cmd_name, "explorer")) {

            // }

            Image img = GenImageChecked(26, 26, 4, 4, BLACK, WHITE);

            _state.icons[i] = LoadTextureFromImage(img);

            UnloadImage(img);
        }
    }

    struct dwm_context *dctx = _ntDwmGetGlobal();
    renderer_state_t *st = _ntRendererGetState();

    st->draw_fps = true;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        rsb_array_Int *pids = _ntDwmGetProcesses(dctx);

        bool window_selected = false;

        for (int i = 0; i < pids->len; i++) {
            struct dwm_window *_wnd = _ntDwmGetProcess(dctx, RSBGetAtIndexInt(pids, i));

            if (_wnd->hidden.state) continue;

            Rectangle sz = {
                _wnd->position.x, _wnd->position.y,
                _wnd->size.x * st->scaling, _wnd->size.y * st->scaling
            };

            if (CheckCollisionPointRec(GetMousePosition(), sz)) {
                window_selected = true;
                _state.icon_pressed_times = 0;
                _state.icon_pressed_id = -1;
                break;
            }
        }

        RSBDestroyInt(pids);

        if (!window_selected) {
            dctx->selected_window = NULL;
            // _state.icon_pressed_times = 0;
            // _state.icon_pressed_id = -1;
        }
    }

    for (int i = 0; i < STATE_ARRAYS_LEN; i++) {
        _ntRendererUpdateAnimation(_state.animations + i);
    }

    if (IsKeyPressed(KEY_T)) {
        explorer_shell_test_animation1();
    }

    if (_state.old_layer.on_update.callback) _state.old_layer.on_update.callback(_state.old_layer.on_update.user);
}

const char *explorer_map_icon(int idx) {
    switch(idx) {
        default:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4: {
            return "explorer";
        }
        case 5: {
            return "msoobe";
        }
        case 6: {
            return "logo";
        }
        case 7: {
            return "setup";
        }
    }
}
