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

#include <nt5emul/pv/select_file.h>
#include <nt5emul/pv/state.h>
#include <nt5emul/renderer.h>
#include <nt5emul/tui/text.h>
#include <nt5emul/tui/menu.h>
#include <nt5emul/tui/rectangle.h>
#include <nt5emul/tui/frame.h>
#include <nt5emul/tui/environment.h>
#include <nt5emul/pv/file_check.h>
#include <nt5emul/pv/peinfo.h>
#include <string.h>

const char *nd_type[6] = {
    "unknown", "resource directory",
    "directory entry", "data string",
    "data entry",

    "(bitmap entry)"
};

void _ntPVDrawResourceTree(pe_resource_node_t *node) {
    if (!node) return;

    if (__state.tree_i > __state.tree_max) return;
    __state.tree_i++;

    Vector2 *v = &__state.tree_current_pos;

    char *type = nd_type[node->type];

    if (node->type == LIBPE_RDT_DATA_ENTRY) {
        IMAGE_RESOURCE_DATA_ENTRY *entry = node->raw.dataEntry;

        type = TextFormat("%s (%d)", type, entry->CodePage);
    }

    _ntTuiDrawText(TextFormat("dirLevel: %d (depth=%d)\ntype: %s",
        node->dirLevel, node->depth, type
    ), v->x, v->y, WHITE);

    // if (node->type == )

    v->y +=  2;

    int old_x = v->x;

    v->x++;
    _ntPVDrawResourceTree(node->childNode);

    v->x = old_x;

    _ntPVDrawResourceTree(node->nextNode);

}

void _ntPVDrawPe2() {
    pe_resource_node_t *root_nd = __state.file_resources->root_node;

    _ntPVDrawResourceTree(root_nd);

    _ntTuiDrawText(TextFormat("tlm: %d", __state.tree_i), 10, 1, WHITE);
}
void _ntPVDrawPe1() {
    Vector2 v = {
        .x = 4,
        .y = 3
    };

    Vector2 v2 = {
        .x = v.x + 20,
        .y = v.y
    };

    Vector2 v3 = {
        .x = v2.x + 20,
        .y = v2.y
    };

    _ntTuiDrawText(TextFormat("sections: %d\ndirectories: %d\ndmin: %d",
        __state.sections, __state.directories, __state.directories_i
    ), v.x, v.y, WHITE);

    for (int i = 0; i < __state.sections; i++) {
        IMAGE_SECTION_HEADER * h = __state.file.pe.sections[i];

        char name[9] = {};
        memcpy(name, h->Name, 8);

        _ntTuiDrawText(TextFormat("section %d info:\n- name: %s",
            i, name
        ), v2.x, v2.y, WHITE);

        v2.y += 3;
    }

    for (int i = __state.directories_i; i < __state.directories && i < __state.directories_i + 8; i++) {
        IMAGE_DATA_DIRECTORY * d = __state.file.pe.directories[i];

        _ntTuiDrawText(TextFormat("directory %d info:\n- size: %d bytes",
            i, d->Size
        ), v3.x, v3.y, WHITE);

        v3.y += 3;
    }
}

void _ntPVDrawPe() {
    _ntTuiDrawText(TextFormat("page %d", __state.page_i + 1), 1, 1, WHITE);

    _ntTuiDrawTextCentered(__state.current_page_name, 0xFF, 1, WHITE);

    switch(__state.page_i) {
        case 0: {
            _ntPVDrawPe1();
            break;
        }
        case 1: {
            _ntPVDrawPe2();
            break;
        }
    }
}
void _ntPVUpdatePe() {
    if (IsKeyPressed(KEY_RIGHT)) {
        __state.page_i++;
    }
    if (IsKeyPressed(KEY_LEFT)) {
        __state.page_i--;

        if (__state.page_i < 0) __state.page_i = 0;
    }

    #define PAGE_MAX 2

    __state.page_max = PAGE_MAX;

    int *i_values[PAGE_MAX] = {
        &__state.directories_i,
        &__state.tree_max
    };

    int *i_val = i_values[__state.page_i % PAGE_MAX];

    if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) {
        (*i_val)--;

        if (*i_val < 0) *i_val = 0;
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
        (*i_val)++;
    }

    switch(__state.page_i) {
        case 0: {
            __state.current_page_name = "PE INTERNAL INFO";

            break;
        }
        case 1: {
            if (!__state.page2_init) {
                __state.file_resources = pe_resources(&__state.file);
                
                Vector2 v = {
                    .x = 4,
                    .y = 3
                };

                __state.tree_pos = v;

                __state.page2_init = true;
            }

            if (IsKeyPressed(KEY_W) || IsKeyPressedRepeat(KEY_W)) {
                __state.tree_pos.y--;
            }
            if (IsKeyPressed(KEY_S) || IsKeyPressedRepeat(KEY_S)) {
                __state.tree_pos.y++;
            }

            __state.current_page_name = "RESOURCES";

            __state.tree_current_pos = __state.tree_pos;

            __state.tree_max = *i_val;
            __state.tree_i = 0;
            
            break;
        }
    }
}