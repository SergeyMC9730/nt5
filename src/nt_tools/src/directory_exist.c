#include <dirent.h> 
#include <stdio.h> 
#include <stdbool.h>

bool _ntDirectoryExist(const char *path) {
    DIR *d = opendir(path);
    
    if (d) {
        closedir(d);

        return true;
    }

    return false;
}