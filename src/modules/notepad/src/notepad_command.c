
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

#include <nt5emul/modules/notepad/state.h>
#include <nt5emul/modules/notepad/notepad_command.h>
#include <nt5emul/dwm/context.h>
#include <nt5emul/dwm/window.h>

#include <nt5emul/renderer.h>

#include <stdio.h>
#include <string.h>

bool notepad_command(void *data) {
    const char **strs;
    char *msg;

    bool create_new_file = false;

    if (!data) {
        create_new_file = true;
    } else {
        strs = (const char **)data;
        msg = strs[1];

        if (!msg) {
            create_new_file = true;
        } else {
            if (strlen(msg) < 1) create_new_file = true;
            else {
                msg[strlen(msg) - 1] = 0;
            }
        }
    }

    struct dwm_window wnd = _ntCreateWindow("notepad", (Vector2){500, 150});

    wnd.draw = notepad_draw;
    wnd.update = notepad_update;
    wnd.on_close = notepad_on_close;

    wnd.filled.state = true;
    wnd.filled.ability = true;

    struct local_notepad_module_state *mod = (struct local_notepad_module_state *)calloc(1, sizeof(struct local_notepad_module_state));

    mod->file_contents = RSBCreateArrayString();
    mod->rendered_file_contents = RSBCreateArrayString();

    struct dwm_context *dwmctx = _ntDwmGetGlobal();
    renderer_state_t *st = _ntRendererGetState();

    struct dwm_context_font fnt = dwmctx->fonts.arial9_std;

    Vector2 base_text_pos = {3, 3};
    Vector2 current_text_pos = base_text_pos;

    Vector2 rsz = {
        wnd.size.x,
        wnd.size.y
    };

    if (!create_new_file) {
        // load string from file path
        const char *str = LoadFileText(msg);

        if (!str) create_new_file = true;
        else {
            size_t sz = strlen(str);

            // copy string into dynamic array
            for (size_t i = 0; i < sz; i++) {
                RSBAddElementString(mod->file_contents, str[i]);
                
                char c = str[i];
                const char cs[] = {c, 0};

                Vector2 csize = MeasureTextEx(fnt.font, cs, fnt.real_size * st->scaling, fnt.spacing * st->scaling);
                
                current_text_pos.x += csize.x + (fnt.spacing * st->scaling);

                // printf("i=%d; c=%c; x=%f\n", i, c, current_text_pos.x);

                if (current_text_pos.x > rsz.x) {
                    current_text_pos.x = base_text_pos.x;

                    RSBAddElementString(mod->rendered_file_contents, '\n');

                    // printf("newline has been placed on %c (%d)\n", c, i);
                }

                RSBAddElementString(mod->rendered_file_contents, c);
            }
        }
    }

    // add \0 string terminator
    RSBAddElementString(mod->file_contents, 0);
    RSBAddElementString(mod->rendered_file_contents, 0);

    wnd.ctx = mod;

    wnd.position = (Vector2){50, 50};
    
    _ntPushWindow(_ntDwmGetGlobal(), wnd);


    return true;
}

void notepad_draw(struct dwm_window *wnd, void *ctx) {
    struct dwm_context *dwmctx = _ntDwmGetGlobal();
    renderer_state_t *st = _ntRendererGetState();
    struct local_notepad_module_state *mod = (struct local_notepad_module_state *)ctx;

    struct dwm_context_font fnt = dwmctx->fonts.arial9_std;

    Vector2 base_text_pos = {3, 3};

    DrawTextEx(fnt.font, mod->rendered_file_contents->objects, base_text_pos, fnt.real_size, fnt.spacing, BLACK);
}

void notepad_update(struct dwm_window *wnd, void *ctx) {
    
}

void notepad_on_close(struct dwm_window *wnd, void *ctx) {
    struct local_notepad_module_state *mod = (struct local_notepad_module_state *)ctx;

    RSBDestroyString(mod->rendered_file_contents);
    RSBDestroyString(mod->file_contents);

    free(mod);
}
