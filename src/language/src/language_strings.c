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
        .str_en = "Thank you for downloading Windows XP simulator.\n\nThis project is very incomplete (including this OOBE).\n* By clicking Skip OOBE would be skipped and you will get into the logonui.\nUser profile would be created automatically.\n* By clicking Next msoobe would load incomplete installation process.",
        .str_ru = "Благодарим за скачивание симулятора Windows XP.\n\nДанный проект очень сырой (включая данный установщик).\n* По нажатию на \"Пропустить\", первоначальная настройка будет пропущена и вы перейдёте в logonui.\nПользовательский профиль будет создан автоматически\n* По нажатию на \"Далее\", первоначальная настройка загрузит незаконченный установщик."
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_msoobe_enter_continue",
        .str_en = "To continue, click Next.",
        .str_ru = "Для продолжение щёлкните \"Далее\"."
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_msoobe_next",
        .str_en = "Next",
        .str_ru = "Далее"
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_msoobe_skip",
        .str_en = "Skip",
        .str_ru = "Пропустить"
    });
    RSBAddElementLanguagePackCell(array, (struct language_pack_cell){
        .internal_name = "cterm_logonui_welcome",
        .str_en = "welcome",
        .str_ru = "приветствие"
    });
    
    return array;
}