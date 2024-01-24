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

#include <nt5emul/modules/explorer/state.h>
#include <nt5emul/renderer.h>
#include <nt5emul/dwm/window.h>
#include <nt5emul/dwm/context.h>
#include <nt5emul/dwm/button.h>
#include <nt5emul/timer.h>
#include <nt5emul/version.h>

#include <stdio.h>

void explorer_shell_mouse_reset(void *ctx) {
    _state.icon_pressed_times = 0;
}

bool explorer_pressed_on_window() {
    struct dwm_context *dctx = _ntDwmGetGlobal();
    renderer_state_t *st = _ntRendererGetState();
    
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        rsb_array_Int *pids = _ntGetDWMProcesses(dctx);

        bool window_selected = false;

        for (int i = 0; i < pids->len; i++) {
            struct dwm_window *_wnd = _ntGetDWMProcess(dctx, RSBGetAtIndexInt(pids, i));
            
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
                        current_pos.x, current_pos.y, _state.icons[i].width, _state.icons[i].height
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

            cterm_command_reference_t ref = _state.runtime->find("CTERM_line_execute");
            if (ref.callback) {
                ref.callback("notify Not implemented yet!\nRunning some programs");
            }

            switch(_state.icon_pressed_id) {
                case 0:
                case 1:
                case 2:
                case 3: 
                case 4: {
                    ref = _state.runtime->find("explorer");
                    if (ref.callback) {
                        ref.callback(NULL);
                    }
                    break;
                }
                case 5: {
                    ref = _state.runtime->find("msoobe");
                    if (ref.callback) {
                        ref.callback(NULL);
                    }
                    break;
                }
                case 6: {
                    ref = _state.runtime->find("logo");
                    if (ref.callback) {
                        ref.callback(NULL);
                    }
                    break;
                }
                case 7: {
                    ref = _state.runtime->find("setup");
                    if (ref.callback) {
                        ref.callback(NULL);
                    }
                    break;
                }
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
        cterm_command_reference_t ref = _state.runtime->find("CTERM_line_execute");
        if (ref.callback) {
            ref.callback("notify Not implemented yet!\nRunning explorer");
        }

        ref = _state.runtime->find("explorer");
        if (ref.callback) {
            ref.callback(NULL);
        }
    }

    return btn.button.x + btn.button.width + (1 * st->scaling);
}

void explorer_shell_draw_watermark(Vector2 offset) {
    const char *str2 = NT5_VERSION;

    Vector2 wsz = {
        GetRenderWidth(),
        GetRenderHeight()
    };
    int sz = 20;

    renderer_state_t *st = _ntRendererGetState();

    Vector2 textsz2 = MeasureTextEx(GetFontDefault(), str2, sz, 1.f * st->scaling);

    Color col = WHITE;
    col.a = 128;

    DrawText(str2, wsz.x - textsz2.x - (20 * st->scaling) + offset.x, wsz.y - textsz2.y - (10 * st->scaling) + offset.y, sz, col);
}

void explorer_shell_draw(void *ctx) {
    Vector2 sz = {
        GetRenderWidth(),
        GetRenderHeight()
    };

    float ratio = 1.f;

    if (_state.background.height > sz.y) {
        ratio = sz.y / (float)_state.background.height;
    }

    if (((float)_state.background.width * ratio) < sz.x) {
        ratio = sz.x / (float)_state.background.width;
    }

    int posX = (sz.x - ((float)_state.background.width * ratio)) / 2;
    int posY = (sz.y - ((float)_state.background.height * ratio)) / 2;

    _ntRendererDrawSizedTexture(_state.background, (Vector2){ratio, ratio}, (Vector2){posX, posY}, (Vector2){}, false);

    struct dwm_context *dctx = _ntDwmGetGlobal();
    renderer_state_t *st = _ntRendererGetState();

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

    rsb_array_Int *pids = _ntGetDWMProcesses(dctx);

    for (int i = 0; i < pids->len; i++) {
        struct dwm_window *_wnd = _ntGetDWMProcess(dctx, RSBGetAtIndexInt(pids, i));

        struct dwm_button btn = {};
        btn.text = _wnd->title;
        btn.button.x = btn_x;
        btn.button.y = taskbar.y;
        btn.button.width = btn_xsz;
        btn.button.height = taskbar.height - (4 * st->scaling);

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

        btn_x += btn_xsz + (4 * st->scaling);
    }

    RSBDestroyInt(pids);

    explorer_shell_draw_icons();

    explorer_shell_draw_watermark((Vector2){0, -taskbar.height});

    if (_state.old_draw) _state.old_draw(_state.old_ctx);
}
void explorer_shell_update(void *ctx) {
    if (_state.background.width == 0) {
        _state.background = LoadTexture("nt/images/user/wallpapers/bliss.jpg");

        SetWindowState(FLAG_WINDOW_RESIZABLE);

        Sound snd = LoadSound("nt/sounds/xpstartu.wav");
        PlaySound(snd);

        for (int i = 0; i < 8; i++) {
            Image img = GenImageChecked(26, 26, 4, 4, BLACK, WHITE);

            _state.icons[i] = LoadTextureFromImage(img);

            UnloadImage(img);
        }
    }

    struct dwm_context *dctx = _ntDwmGetGlobal();
    renderer_state_t *st = _ntRendererGetState();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        rsb_array_Int *pids = _ntGetDWMProcesses(dctx);

        bool window_selected = false;

        for (int i = 0; i < pids->len; i++) {
            struct dwm_window *_wnd = _ntGetDWMProcess(dctx, RSBGetAtIndexInt(pids, i));
            
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

    if (_state.old_update) _state.old_update(_state.old_ctx);
}