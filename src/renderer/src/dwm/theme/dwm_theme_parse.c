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

#include <nt5emul/dwm/theme.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct dwm_theme_color_mapping {
    const char *key;
    Color *value;
};

int _ntParseDwmTheme(void *user, const char *section, const char *name, const char *value) {
    int hash = strcmp(name, "GradientInactiveTitle");

    // printf("section: %s | name: %s (%d) | value: %s\n", section, name, hash, value);

    // check if current section is the colors
    if (!strcmp(section, "Control Panel\\Colors")) {
        struct dwm_theme *theme = (struct dwm_theme *)user;

        int i = 0;

        int colrgb[3] = {0};

        // copy value to value_copy with allocation
        char *value_copy = (char *)malloc(strlen(value) + 1);
        TextCopy(value_copy, value);

        // start splitting value_copy by " "
        char *tk = strtok(value_copy, " ");

        while (tk != NULL && i < 3) {
            // parse integer value and put to colrgb
            colrgb[i] = atoi(tk);

            i++;

            // get next token
            tk = strtok(NULL, " ");
        }

        // free memory
        free(value_copy);

        // create color value
        Color c = {
            colrgb[0], colrgb[1], colrgb[2],
            0xFF
        };
        Color c_unk;

        Color *_c = &c_unk;
        
        #define CMP(n) if (!strcmp(name, n))
        #define MAP_LENGTH 29

        // create color mapping
        struct dwm_theme_color_mapping map[MAP_LENGTH] = {
            {"ActiveTitle", &theme->basic.window_active_title_gradient[0]},
            {"GradientActiveTitle", &theme->basic.window_active_title_gradient[1]},
            {"Hilight", &theme->basic.highlight_color},
            {"InactiveTitle", &theme->basic.window_inactive_title_gradient[0]},
            {"Window", &theme->basic.window_base_color},
            {"WindowText", &theme->basic.window_base_text_color},
            {"WindowFrame", &theme->basic.window_frame_color},
            {"Scrollbar", &theme->basic.scrollbar_color},
            {"TitleText", &theme->basic.active_title_text_color},
            {"InactiveTitleText", &theme->basic.inactive_title_text_color},
            {"ButtonFace", &theme->basic.button_face_color},
            {"ButtonShadow", &theme->basic.button_shadow_color},
            {"ButtonText", &theme->basic.button_face_color},
            {"ButtonHilight", &theme->basic.button_highlight_color},
            {"ButtonDkShadow", &theme->basic.button_dk_shadow},
            {"ButtonLight", &theme->basic.button_light_color},
            {"ButtonAlternativeFace", &theme->basic.button_alternative_face_color},
            {"HotTrackingColor", &theme->basic.hot_tracking_color},
            {"InfoText", &theme->basic.info_text_color},
            {"InfoWindow", &theme->basic.info_window_color},
            {"Menu", &theme->basic.menu_color},
            {"MenuText", &theme->basic.menu_text_color},
            {"MenuHilight", &theme->basic.menu_highlight_color},
            {"MenuBar", &theme->basic.menu_bar_color},
            {"GrayText", &theme->basic.gray_text_color},
            {"AppWorkspace", &theme->basic.app_workspace_color},
            {"InactiveBorder", &theme->basic.inactive_border_color},
            {"ActiveBorder", &theme->basic.active_border_color},
            {"Background", &theme->basic.background_color},
        };
        i = 0;

        while (i < MAP_LENGTH) {
            struct dwm_theme_color_mapping el = map[i];

            // check if current name equals to the name inside the mapping
            if (!strcmp(name, el.key)) {
                // printf("setting up %s to %d %d %d\n", name, c.r, c.g, c.b);
                _c = el.value;
            }

            i++;
        }

        // set color value
        *_c = c;
    }

    return 1;
}