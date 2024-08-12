/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  SergeyMC9730

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

    Contact SergeyMC9730 -- @dogotrigger in Discord
*/

#pragma once

#include <nt5emul/dwm/button.h>
#include <nt5emul/dwm/context_menu.h>
#include <nt5emul/dwm/font.h>

enum DwmGuiObjectType {
    BuilderText = 0,
    BuilderImage,
    BuilderButton
};

#pragma pack(push, 1)

// base structure for all gui objects
struct dwm_gui_object {
    Vector2 position;
    float scale;

    enum DwmGuiObjectType type;
    void *object_reference;
};

struct dwm_gui_text {
    struct dwm_context_font font;
    const char *text;
};

struct dwm_gui_image {
    Texture2D texture;
    
    const char *path;
};

#pragma pack(pop)

struct dwm_gui_objects {
    struct dwm_gui_object *objects;
    unsigned int objects_count;

    void *cJSON_instance;
};

// builds from json file
struct dwm_gui_objects *_ntDwmBuildGui(const char *ui_path);