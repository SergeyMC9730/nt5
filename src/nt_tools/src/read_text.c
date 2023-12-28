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

#include <stdlib.h>
#include <stdio.h>

const char *_ntReadTextFile(const char *path) {
    FILE *file = fopen(path, "rt");

    if (!file) return 0;

    fseek(file, 0, SEEK_END);
    unsigned int size = (unsigned int)ftell(file);
    fseek(file, 0, SEEK_SET);

    if (!size) return 0;

    // size + zero char
    char *text = (char *)malloc(size + 1);

    unsigned int count = (unsigned int)fread(text, sizeof(char), size, file);

    if (count < size) text = realloc(text, count + 1);

    text[count] = '\0';

    fclose(file);

    return text;
}