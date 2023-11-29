#include <nt5emul/bi/frame.h>
#include <nt5emul/bi/rectangle.h>
#include <nt5emul/bi/text.h>
#include <nt5emul/bi/input.h>

#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

#define FIELD_SIZE 64

bool _status_bar_is_error = false;
const char *_status_bar_error = NULL;

void _boot_install_s6error_end() {
    _status_bar_is_error = false;
}

extern void _boot_install_timer(void(*callback)(), float seconds);

void _boot_install_s6error_begin(const char *error) {
    if (_status_bar_is_error) return;
    
    _status_bar_is_error = true;

    _status_bar_error = error;

    _boot_install_timer(_boot_install_s6error_end, 0.5f);
}

void _boot_install_update_step6() {
    _biUpdateInput(__state.buffers[3], FIELD_SIZE);

    if (IsKeyPressed(KEY_ENTER)) {
        if (DirectoryExists(__state.buffers[3])) {
            _boot_install_beginstep7();
        } else {
            _boot_install_s6error_begin(__boot_install_strings[36]);
        }
    }
}

void _boot_install_draw_step6() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};

    const char *status = (_status_bar_is_error) ? _status_bar_error :  __boot_install_strings[34];

    if (!_status_bar_is_error) {
        _biDrawBackground(__boot_install_strings[7], status);
    } else {
        _biDrawBackgroundEx(__boot_install_strings[7], status, (Color){0x00, 0x09, 0xAB, 0xFF}, RED, WHITE);
    }

    _biTextDraw(__boot_install_strings[35], 3, 4, gray);

    size_t l = FIELD_SIZE;

    _biDrawInput(__state.buffers[3], l, (Vector2){(80 - l) / 2, 15}, BLACK, WHITE);
}