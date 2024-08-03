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
#include <stdio.h>
#include <string.h>

const char *_ntGetStringInLanguagePack(rsb_array_LanguagePackCell *pack, const char *i_name, const char *language) {
    int lang_offset = 1;

    printf("lang: %s (comp=%d) ; string=", language, strcmp(language, "ru"));

    if (!strcmp(language, "ru")) {
        lang_offset = 2;
    }

    struct language_pack_cell cell = _ntFindInLanguagePack(pack, i_name);
    
    const char **ptr = (const char **)(&cell);

    const char *string = ptr[lang_offset];

    printf("0x%08llX (%s)\n", (unsigned long long)string, string);

    return string;
}