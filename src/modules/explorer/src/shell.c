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

#include <stdio.h>

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

    rsb_array_Int *pids = _ntGetDWMProcesses(dctx);

    Rectangle taskbar = {
        .x = 0,
        .y = sz.y - (26 * st->scaling),
        .height = 26 * st->scaling,
        .width = sz.x
    };

    DrawRectanglePro(taskbar, (Vector2){}, 0.f, border1);

    int btn_x = taskbar.x;
    int btn_xsz = 50 * st->scaling;

    for (int i = 0; i < pids->len; i++) {
        struct dwm_window *_wnd = _ntGetDWMProcess(dctx, RSBGetAtIndexInt(pids, i));

        struct dwm_button btn = {};
        btn.text = _wnd->title;
        btn.button.x = btn_x;
        btn.button.y = taskbar.y + 1;
        btn.button.width = btn_xsz;
        btn.button.height = taskbar.height - 2;

        btn.howered.ability = true;
        btn.activated.ability = true;

        if (_ntDrawDWMButton(dctx, &btn)) {
            dctx->selected_window = _wnd;
        }

        btn_x += btn_xsz + (4 * st->scaling);
    }

    RSBDestroyInt(pids);

    if (_state.old_draw) _state.old_draw(_state.old_ctx);
}
void explorer_shell_update(void *ctx) {
    if (_state.background.width == 0) {
        _state.background = LoadTexture("nt/images/user/wallpapers/bliss.jpg");

        SetWindowState(FLAG_WINDOW_RESIZABLE);
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
                break;
            }
        }

        RSBDestroyInt(pids);

        if (!window_selected) {
            dctx->selected_window = NULL;
        }
    }

    if (_state.old_update) _state.old_update(_state.old_ctx);
}