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


#pragma once

#include <raylib.h>

#include <nt5emul/renderer.h>
#include <nt5emul/renderer_animation.h>

struct cterm_instance;

struct module_state {
    struct cterm_instance *runtime;

    bool execution_lock;

    renderer_layer_t old_layer;

    Texture2D background;

    Texture2D icons[8];

    const char *cterm_shell_start_classic;

    const char *cterm_shell_intro_title;
    const char *cterm_shell_intro_text;

    int id;

    int icon_pressed_times;
    int icon_pressed_id;

    Texture ico100;
    Texture ico252;

    const char *cterm_explorer_title;
    const char *cterm_explorer_system_tasks;
    const char *cterm_explorer_other_places;
    const char *cterm_explorer_st_vsi;
    const char *cterm_explorer_st_arp;
    const char *cterm_explorer_st_cs;
    const char *cterm_explorer_op_nmp;
    const char *cterm_explorer_op_md;
    const char *cterm_explorer_op_sd;
    const char *cterm_explorer_op_cp;

#define STATE_ARRAYS_LEN 64

    struct renderer_animation animations[STATE_ARRAYS_LEN];
    // struct dwm_button taskbar_apps[STATE_ARRAYS_LEN];
};

extern struct module_state _state;

#include <nt5emul/modules/explorer/local_state.h>