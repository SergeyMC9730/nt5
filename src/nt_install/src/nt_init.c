#include <nt5emul/bi/text.h>
#include <nt5emul/renderer.h>
#include <nt5emul/nt_install.h>
#include <nt5emul/boot_install_settings.h>
#include <nt5emul/bi/timer.h>
#include <nt5emul/boot_install_steps.h>

#include <cJSON.h>
#include <stdio.h>

// expose internal values

extern char *__boot_install_strings[BOOT_INSTALL_STRING_ARRAY_SIZE]; // all strings
extern ntinstall_t __state; // installation state

// expose NT renderer
extern renderer_state_t _renderer_state;

void _boot_install_create_config() {
    // create json object
    cJSON *j = cJSON_CreateObject();
    cJSON *setup_completed = cJSON_CreateBool(true);

    cJSON_AddItemToObject(j, "setup_completed", setup_completed);

    // convert json object into a string
    char *str = cJSON_Print(j);

    // open config.json stream
    FILE *fp = fopen("nt/config.json", "w");

    // write json object
    fputs(str, fp);
    fclose(fp);

    // destroy json object;
    cJSON_free(str);
    cJSON_Delete(j);
}

void _boot_install_step9_config() {
    _boot_install_create_config();

    _boot_install_beginstep10();
}

void _boot_install_update_step9() {
    _boot_install_timer(_boot_install_step9_config, 1.f / (float)GetFPS());

    _renderer_state.layers[1].update = NULL;
}

void _boot_install_draw_step9() {
    Color gray = (Color){0xA8, 0xA8, 0xA8, 0xFF};

    // Please wait while Setup initializes your NT XP configuration.
    _biTextDrawCentered(__boot_install_strings[51], 0xFF, 7, gray);
}