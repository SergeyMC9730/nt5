#include <string.h>
#include <stdlib.h>

char *_ntCopyString(const char *str) {
    size_t len = strlen(str);

    char *val = (char *)calloc(1, len + 1);
    strcpy(val, (const char *)str);

    return val;
}