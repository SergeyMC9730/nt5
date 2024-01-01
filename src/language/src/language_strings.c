#include <nt5emul/language_pack.h>

RSB_ARRAY_IMPL_GEN(struct language_pack_cell, LanguagePackCell);

#include <string.h>

struct language_pack_cell _ntFindInLanguagePack(const char *internal_name, rsb_array_LanguagePackCell *pack) {
    if (!pack) return (struct language_pack_cell){};
    
    for (int i = 0; i < pack->len; i++) {
        struct language_pack_cell cell = RSBGetAtIndexLanguagePackCell(pack, i);

        if (!strcmp(cell.internal_name, internal_name)) {
            return cell;
        }
    }

    return (struct language_pack_cell){};
}

rsb_array_LanguagePackCell *_ntGenerateLanguagePack() {
    rsb_array_LanguagePackCell *array = RSBCreateArrayLanguagePackCell();

    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_setup_installing_devices",
        .str_en = "Installing Devices",
        .str_ru = "Установка устройств"
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_setup_installing_network",
        .str_en = "Installing Network",
        .str_ru = "Установка поддержки\nсети"
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_setup_copying_files",
        .str_en = "Copying files...",
        .str_ru = "Копирование файлов..."
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_setup_completing_install",
        .str_en = "Completing installation...",
        .str_ru = "Завершение установки..."
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_setup_installing_start",
        .str_en = "Installing Start menu items",
        .str_ru = "Установка элементов\nменю Пуск"
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_setup_registering_components",
        .str_en = "Registering components",
        .str_ru = "Регистрация компонентов"
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_setup_saving_settings",
        .str_en = "Saving settings",
        .str_ru = "Сохранение параметров"
    });

    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_setup_time_approx",
        .str_en = "Setup will complete in\napproximately:\n   %d minutes",
        .str_ru = "Установка будет\nзавершена через:\n   %d мин."
    });

    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_setup_colinfo",
        .str_en = "Collecting\ninformation",
        .str_ru = "Сбор\nсведений"
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_setup_dynupd",
        .str_en = "Dynamic\nUpdate",
        .str_ru = "Динамическое\nобновление"
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_setup_prepinst",
        .str_en = "Preparing\ninstallation",
        .str_ru = "Подготовка к\nустановке"
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_setup_instwin",
        .str_en = "Installing\nWindows",
        .str_ru = "Установка\nWindows"
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_setup_final",
        .str_en = "Finalizing\ninstallation",
        .str_ru = "Завершение\nустановки"
    });

    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_msoobe_welcome",
        .str_en = "Welcome to NT5 simulator",
        .str_ru = "Добро пожаловать в симулятор NT5"
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_msoobe_incomplete",
        .str_en = "Thank you for downloading Windows XP simulator.\n\n\nThis project is very incomplete (including this OOBE).\nBy pressing Enter OOBE would be skipped and you will get into the logonui.",
        .str_ru = "Благодарим за скачивание симулятора Windows XP.\n\n\nДанный проект очень сырой (включая данный установщик).\nПо нажатию на Enter, установщик будет пропущен и вы перейдёте в logonui."
    });
    
    return array;
}