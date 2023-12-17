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

#include <raylib.h>

struct dwm_basic_theme {
    Color highlight_color; // Hilight
    Color highlight_text_color; // HilightText

    // ActiveTitle -> GradientActiveTitle
    Color window_active_title_gradient[2];
    // InactiveTitle -> GradientInactiveTitle
    Color window_inactive_title_gradient[2];

    Color window_base_color; // Window
    Color window_base_text_color; // WindowText
    Color window_frame_color; // WindowFrame

    Color scrollbar_color; // Scrollbar

    Color active_title_text_color; // TitleText
    Color inactive_title_text_color; // InactiveTitleText

    Color button_face_color; // ButtonFace
    Color button_shadow_color; // ButtonShadow
    Color button_text_color; // ButtonText
    Color button_highlight_color; // ButtonHilight
    Color button_dk_shadow; // ButtonDkShadow
    Color button_light_color; // ButtonLight
    Color button_alternative_face_color; // ButtonAlternativeFace

    Color hot_tracking_color; // HotTrackingColor

    Color info_text_color; // InfoText

    Color info_window_color; // InfoWindow

    Color menu_color; // Menu
    Color menu_text_color; // MenuText
    Color menu_highlight_color; // MenuHilight
    Color menu_bar_color; // MenuBar

    Color gray_text_color; // GrayText

    Color app_workspace_color; // AppWorkspace

    Color inactive_border_color; // InactiveBorder
    Color active_border_color; // ActiveBorder

    Color background_color; // Background

    int title_bar_size;

    const char *theme_path;
};