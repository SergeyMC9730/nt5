#include <nt5emul/boot_install.h>

#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h> 
#include <stdio.h> 
#include <string.h>

#include <nt5emul/bi/xp_detection.h>
#include <nt5emul/timer.h>

// expose internal values

extern ntinstall_t __state; // installation state

void _boot_install_detect_xp() {
    // try to find mounted xp image

    // get user
    char *user = getenv("USER");
    
    // allocate buffer
    char *buffer = (char *)MemAlloc(256);

    snprintf(buffer, 256, "/media/%s/", user);

    // try to open directory
    DIR *d = opendir(buffer);
    struct dirent *dir;

    bool found = false;

    if (d) {
        // go through each file
        while ((dir = readdir(d)) != NULL) {
            const char *name = dir->d_name;

            // check if directory's name has XP signs
            if(!strncmp(name, "GRTMP", 5)) {
                // we found windows xp drive
                snprintf(buffer, 256, "/media/%s/%s/i386", user, name);

                found = true;
            }
        }
        closedir(d);
    }

    if (found) {
        // copy path to the input string
        strncpy(__state.buffers[3], buffer, 64);
    }

    // free buffer
    MemFree(buffer);

    if (__state.detection_required) _ntInstallTimer(_boot_install_detect_xp, 0.5f);
}