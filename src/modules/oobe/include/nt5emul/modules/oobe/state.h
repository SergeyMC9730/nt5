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

#include <cterm/applications/api.h>
#include <raylib.h>

#include <nt5emul/dwm/context.h>
#include <nt5emul/dwm/video.h>

struct module_state {
    cterm_t *runtime;

    Texture2D logo_texture;
    Texture2D main_bg_texture;

    Texture2D line_bottom_texture;
    Texture2D line_top_texture;

    Texture2D radio_off_texture;
    Texture2D radio_on_texture;

    Texture2D square_next_texture_off;
    Texture2D square_next_texture_on;

    Texture2D square_skip_texture_off;
    Texture2D square_skip_texture_on;

    struct dwm_context *dwm_ctx;

    bool init_complete;

    void (*old_draw)(void *user);
    void (*old_update)(void *user);
    void *old_ctx;

    int minutes_left;

    bool execution_lock;

    struct dwm_video xp_vid;
    int frame_1;
    int frame_2;

    int old_fps;
    
    Sound music_title;

    const char *cterm_setup_installing_devices;
    const char *cterm_setup_installing_network;
    const char *cterm_setup_copying_files;
    const char *cterm_setup_completing_install;
    const char *cterm_setup_installing_start;
    const char *cterm_setup_registering_components;
    const char *cterm_setup_saving_settings;
    const char *cterm_setup_time_approx;
    const char *cterm_setup_colinfo;
    const char *cterm_setup_dynupd;
    const char *cterm_setup_prepinst;
    const char *cterm_setup_instwin;
    const char *cterm_setup_final;

    const char *cterm_msoobe_welcome;
    const char *cterm_msoobe_incomplete;
    const char *cterm_msoobe_enter_continue;
    const char *cterm_msoobe_next;
    const char *cterm_msoobe_skip;
};

extern struct module_state _state;

const char *get_string(const char *i, const char *l);