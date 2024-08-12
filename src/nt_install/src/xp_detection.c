/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2024  Sergei Baigerov

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

#include <nt5emul/boot_install.h>

#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h> 
#include <stdio.h> 
#include <string.h>

#include <nt5emul/bi/xp_detection.h>
#include <nt5emul/timer.h>
#include <nt5emul/copy_string.h>

// expose internal values

extern ntinstall_t __state; // installation state

void _boot_install_detect_xp() {
    // try to find mounted xp image

    // get user
    char *user = getenv("USER");
    
    // allocate buffer
    char *buffer = (char *)MemAlloc(512);

    bool found = false;

    static const char *paths[2] = {
        "/media/%s",
        "/run/media/%s"
    };

    // go through each path declared in the paths variable
    for (int i = 0; i < sizeof(paths) / sizeof(const char *); i++) {
        const char *fmt_path = paths[i];

        snprintf(buffer, 512, fmt_path, user);

        // try to open directory
        DIR *d = opendir(buffer);
        struct dirent *dir;

        if (d) {
            // go through each file
            while ((dir = readdir(d)) != NULL) {
                const char *name = dir->d_name;

                if (found) {
                    break;
                }

                // check if directory's name has any XP mentions
                if(
                    !strncmp(name, "GRTM", 4)   || // standard xp disk
                    !strncmp(name, "TABL", 4)   || // tablet pc edition disk
                    !strncmp(name, "CD_ROM", 6) || // disk with windows xp compiled from the source code (open xp)
                    strstr(name, "XP") !=  NULL || // disk with custom label (has XP)
                    strstr(name, "Xp") !=  NULL || // disk with custom label (has Xp)
                    strstr(name, "xp") !=  NULL || // disk with custom label (has xp)
                    strstr(name, "Win") != NULL || // disk with custom label (has Win)
                    strstr(name, "WIN") != NULL || // disk with custom label (has WIN)
                    strstr(name, "win") != NULL    // disk with custom label (has win)
                ) {
                    // we found windows xp drive
                    // now check which architecture this os has been built for

                    bool valid_arch = false;

                    // copy current buffer
                    char *old_buffer = _ntCopyString(buffer);

                    // test i386
                    if (!valid_arch) snprintf(buffer, 512, "%s/i386", old_buffer, name);
                    if (DirectoryExists(buffer)) {
                        // it is i386 ok
                        valid_arch = true;
                    }

                    // test amd64
                    if (!valid_arch) snprintf(buffer, 512, "%s/amd64", old_buffer, name);
                    if (DirectoryExists(buffer)) {
                        // it is amd64 ok
                        valid_arch = true;
                    }

                    MemFree(old_buffer);

                    found = valid_arch;
                }
            }
            closedir(d);
        }

        if (found) {
            break;
        }
    }

    if (found) {
        // copy path to the input string
        strncpy(__state.buffers[3], buffer, 64);
    }

    // free buffer
    MemFree(buffer);

    if (__state.detection_required) _ntInstallTimer(_boot_install_detect_xp, 0.5f, NULL);
}