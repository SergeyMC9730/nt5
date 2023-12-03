#include <nt5emul/renderer.h>

#include <nt5emul/tui/environment.h>

#include <nt5emul/tui/text.h>
#include <nt5emul/tui/menu.h>

#include <nt5emul/ext/rsb_array_gen.h>

RSB_ARRAY_DEF_GEN(const char *, String)
RSB_ARRAY_IMPL_GEN(const char *, String)

struct nt_file_selector_menu {
    // base menu
    struct nt_tui_menu base;

    const char *path;

    rsb_array_String *listing;
    
    // false - want folder
    // true  - want file
    bool want_file;

    int items_per_page;
    int page;

    void (*callback)(struct nt_file_selector_menu *menu, const char *file_path);
};

struct nt_file_selector_menu *menu0;

#include <dirent.h> 
#include <stdio.h> 
#include <string.h>

void set_fileselection_listing(struct nt_file_selector_menu *m) {
    DIR *d = opendir(m->path);
    struct dirent *dir;

    if (d) {
        size_t i = 0;

        while (i < m->listing->len) {
            const char *str = RSBGetAtIndexString(m->listing, i);
            free((char *)str);

            i++;
        }

        i = 0;
        while (m->listing->len != 0) {
            RSBPopElementString(m->listing);

            i++;
        }

        i = 0;

        int has_prev = 0;

        if (m->page >= 1) {
            char *prev_page_str = "[ PREV PAGE ]";

            size_t l = strlen(prev_page_str) + 1;

            char *prev_page = (char *)malloc(l);

            memset(prev_page, 0, l);

            strncpy(prev_page, prev_page_str, l - 1);

            RSBAddElementString(m->listing, prev_page);

            has_prev = 1;
        }

        int pg_index_max = m->items_per_page * (m->page + 1);

        printf(" - page: %d\n - index max - %d\n", m->page, pg_index_max);

        while (((dir = readdir(d)) != NULL) && i < pg_index_max) {
            if (i < (m->page * m->items_per_page)) {
                i++;

                continue;
            }

            const char *str_r = dir->d_name;

            size_t l = strlen(str_r) + 3;

            char *str_a = (char *)malloc(l);

            const char *folder_open = " >";

            if (!DirectoryExists(dir->d_name)) {
                folder_open = "";
            }

            snprintf(str_a, l, "%s%s", str_r, folder_open);

            RSBAddElementString(m->listing, (const char *)str_a);

            i++;
        }

        if (m->listing->len == (m->items_per_page + has_prev)) {
            char *next_page_str = "[ NEXT PAGE ]";

            size_t l = strlen(next_page_str) + 1;

            char *next_page = (char *)malloc(l);

            memset(next_page, 0, l);

            strncpy(next_page, next_page_str, l - 1);

            RSBAddElementString(m->listing, next_page);
        }

        closedir(d);

        m->base.selected_item = 0;
    }

    m->base.items_total = m->listing->len;
    m->base.objects = m->listing->objects;
}

void update_fileselection_click(int idx, struct nt_tui_menu *menu) {
    printf("test %d\n", idx);

    struct nt_file_selector_menu *m = (struct nt_file_selector_menu *)menu->ptr;

    const char *obj = RSBGetAtIndexString(m->listing, idx);

    if (!strcmp(obj, "[ NEXT PAGE ]")) {
        m->page++;

        set_fileselection_listing(m);

        return;
    } else if (!strcmp(obj, "[ PREV PAGE ]")) {
        m->page--;

        set_fileselection_listing(m);

        return;
    }

    size_t basefile = strlen(obj);
    size_t basepath = strlen(m->path);

    if (obj[basefile - 1] == '>') {
        ((char *)obj)[basefile - 2] = 0;
    } 

    size_t l1 = strlen(m->path) + strlen(obj) + 4;

    char *filepath = malloc(l1);

    snprintf(filepath, l1, "%s/%s", m->path, obj);

    printf("file: %s\n", filepath);

    if (DirectoryExists(filepath)) {
        if (m->want_file) {
            free((char *)m->path);
            m->path = filepath;

            m->page = 0;

            set_fileselection_listing(m);
        } else {
            if (m->callback != NULL) {
                m->callback(m, filepath);

                free(filepath);
            }
        }
    } else {
        if (m->want_file && m->callback != NULL) {
            m->callback(m, filepath);

            free(filepath);
        }
    }
}

void update_fileselection_menu(struct nt_file_selector_menu *menu) {
    _ntUpdateMenu(&menu->base);

}


struct nt_file_selector_menu *create_fileselection_menu(const char *path, int items_per_page) {
    struct nt_file_selector_menu *m = (struct nt_file_selector_menu *)malloc(sizeof(struct nt_file_selector_menu));

    m->base.selected_background_color = WHITE;
    m->base.selected_text_color = BLACK;
    m->base.unselected_text_color = WHITE;

    m->base.ptr = m;

    m->base.click_handler = update_fileselection_click;

    char *p = malloc(strlen(path) + 1);
    strcpy(p, path);

    m->path = p;
   
    m->listing = RSBCreateArrayString();

    m->want_file = true;

    m->items_per_page = items_per_page;
    m->page = 0;

    m->callback = NULL;

    set_fileselection_listing(m);

    return m;
}

void update1() {
    update_fileselection_menu(menu0);
}

void update() {
    renderer_state_t *st = _ntRendererGetState();

    // init text ui environment
    _ntTuiLoadEnvironmentDefault();

    st->layers[0].update = update1;
}

void draw() {
    Color gray = (Color){ 30, 30, 30, 255 };

    ClearBackground(gray);

    // _ntTuiDrawTextCentered("hello", 0xFF, 10, WHITE);

    _ntTuiDrawMenu(menu0->base);
}

int main() {
    // init NT renderer
	_ntRendererCreateEnvironment();

    renderer_state_t *st = _ntRendererGetState();

    st->layers[0].draw = draw;
    st->layers[0].update = update;

    menu0 = create_fileselection_menu("./", 10);

    menu0->base.x = 10;
    menu0->base.y = 10;

    _ntRendererJoin();
}