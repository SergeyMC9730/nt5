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
#include <nt5emul/dwm/context.h>
#include <nt5emul/renderer.h>
#include <nt5emul/dwm/window.h>
#include <nt5emul/tui/text.h>

#ifndef NULL
#define NULL (void *)0
#endif

#include <stdio.h>

void explorer_draw_sidebar_box(Vector2 pos, const char *title, const char **elements) {
    struct dwm_context *ctx = _ntDwmGetGlobal();
    
    // DrawRectangleRoundedLines()
    renderer_state_t *st = _ntRendererGetState();
    
    int _bSzX = 185.f * st->scaling;
    int _bSzY = 25.f * st->scaling;

    pos.x += (1.f * st->scaling);
    
    Rectangle _b;
    _b.x = pos.x;
    _b.y = pos.y;
    _b.width = _bSzX - (1.f * st->scaling);
    _b.height = _bSzY;

    Color gr1 = WHITE;
    Color gr2 = WHITE;
    gr2.r = 198;
    gr2.g = 211;
    gr2.b = 247;

    // DrawRectangleRoundedLines(_b, 0.35f, 16.f, 1.f, WHITE);

    // pos.x += 1.f * st->scaling;
    // pos.y += 1.f * st->scaling;

    int _tempY = 78.f * st->scaling;

    struct dwm_context_font fontstd = _ntDwmGetFont(ctx, "tahoma9");

    if (elements != NULL) {
        _tempY = (20.f * st->scaling);

        int count = 0;
        while (elements[count] != NULL) {
            Vector2 sz = MeasureTextEx(fontstd.font, elements[count], fontstd.real_size, fontstd.spacing);

            _tempY += sz.y + (4 * st->scaling);

            count++;
        };

    }
    
    Color col2 = WHITE;
    col2.r = 214;
    col2.g = 223;
    col2.b = 247;

    DrawRectangle(pos.x, pos.y + _b.height, _b.width, _tempY - (1.f * st->scaling), col2);
    DrawRectangleLines(pos.x, pos.y + _b.height - (1.f * st->scaling), _b.width, _tempY, WHITE);

    DrawRectangle(pos.x, pos.y, _b.width - (98.f * st->scaling), _b.height, gr1);
    
    pos.x += 85.f * st->scaling;

    DrawRectangleGradientH(pos.x, pos.y, _b.width - (85.f * st->scaling), _b.height, gr1, gr2);

    if (!title) return;

    // get bold tahoma font from the DWM
    struct dwm_context_font font = _ntDwmGetFont(ctx, "tahomabd9");
    
    Vector2 titleSz = MeasureTextEx(font.font, title, font.real_size, font.spacing);

    int titleY = (_bSzY - titleSz.y) / 2;
    Color titleColor = {33, 93, 198, 255};

    pos.x -= 85.f * st->scaling;

    Rectangle titlebar = {
        pos.x, pos.y, _bSzX, _bSzY
    };

    Vector2 m = _ntDwmGetLocalMousePosition(ctx);

    if (CheckCollisionPointRec(m, titlebar)) {
        titleColor.r += 50;
        titleColor.g += 50;
        titleColor.b += 50;
    }

    BeginScissorMode(pos.x, pos.y, _bSzX, _bSzY);
    DrawTextEx(font.font, title, (Vector2){pos.x + (14.f * st->scaling), pos.y + titleY}, font.real_size, font.spacing, titleColor);
    EndScissorMode();

    if (elements == NULL) return;

    int _y = pos.y + _b.height + (10 * st->scaling);

    BeginScissorMode(pos.x, pos.y, _b.width, _b.height + _tempY);

    int i = 0;
    while (elements[i] != NULL) {
        Vector2 sz = MeasureTextEx(fontstd.font, elements[i], fontstd.real_size, fontstd.spacing);

        Color c = {33, 93, 198, 255};

        DrawTextEx(fontstd.font, elements[i], (Vector2){pos.x + (16 * st->scaling), _y}, fontstd.real_size, fontstd.spacing, c);

        _y += sz.y + (4 * st->scaling);

        i++;
    }

    EndScissorMode();
}

void explorer_draw_sidebar1(struct dwm_window *wnd, void *user) {
    struct dwm_context *ctx = _ntDwmGetGlobal();
    struct local_module_state *lst = (struct local_module_state *)user;

    Color _start = WHITE;
    _start.r = 123; 
    _start.g = 162;
    _start.b = 231;

    Color _end = WHITE;
    _end.r = 99;
    _end.g = 117;
    _end.b = 214;

    renderer_state_t *st = _ntRendererGetState();

    int offset = 1.f * st->scaling;
    int xsz = 209.f * st->scaling;
    int ysz = wnd->framebuffer.texture.height;

    Rectangle r;
    r.x = offset;
    r.y = 0;
    r.width = xsz;
    r.height = ysz;

    DrawRectangleGradientEx(r, _start, _end, _end, _end);

    int cX = (xsz - 185.f * st->scaling) / 2;

    const char *table[] = {
        "View system information", "Add or remove programs", "Change a setting", NULL
    };

    explorer_draw_sidebar_box((Vector2){cX, 13.f * st->scaling}, "System Tasks", table);

    const char *table2[] = {
        "My Network Places ", "My Documents", "Shared Documents", "Control Panel", NULL
    };

    explorer_draw_sidebar_box((Vector2){cX, 125.f * st->scaling}, "Other Places", table2);
}

void explorer_draw(struct dwm_window *wnd, void *user) {
    struct dwm_context *ctx = _ntDwmGetGlobal();
    struct local_module_state *lst = (struct local_module_state *)user;

    // // printf("Explorer draw! (%d)\n", lst->fs->base.items_total);

    // Vector2 sz;
    // sz.x = wnd->framebuffer.texture.width;
    // sz.y = wnd->framebuffer.texture.height;

    // // printf("y: %d\n", wnd->framebuffer.texture.height / 2);

    // float offset = ((float)GetRenderHeight() * 181.f) / 420.f;

    // Vector2 scr_pos;
    // scr_pos.x = (int)wnd->content_position.x;
    // scr_pos.y  = GetRenderHeight() - wnd->position.y + offset;

    // if (wnd->moving.state || wnd->post_moving.state) {
    //     Vector2 delta = GetMouseDelta();
        
    //     scr_pos.x += delta.x;
    //     scr_pos.y += delta.y;
    // }

    // _ntRendererDrawScreenPortion((Vector2){}, scr_pos, sz);

    // Color col = BLACK;
    // col.a = 220;

    // DrawRectangle(0, 0, sz.x, sz.y, col);

    // Vector2 m = _ntDwmGetLocalMousePosition(ctx);

    // DrawRectangle(m.x, m.y, 8, 8, RED);

    // _ntTuiDrawMenu(lst->fs->base);
    ClearBackground(WHITE);

    explorer_draw_sidebar1(wnd, user);

    // _ntRendererRunLuaScript("test.lua");
}