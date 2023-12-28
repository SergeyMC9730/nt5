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

#include <pthread.h>
#include <nt5emul/ntcore.h>
#include <nt5emul/timer.h>

struct bi_timer {
    unsigned long long ms;

    void (*callback)();
};

#include <time.h>
#include <errno.h> 

#include <stdlib.h>

void _nt_timer_thread(struct ntcore core, void *arg) {
    struct bi_timer *timer = (struct bi_timer *)arg;

    struct timespec ts;
    int res;

    if (timer->ms < 0) {
        errno = EINVAL;
        return;
    }

    ts.tv_sec = timer->ms / 1000;
    ts.tv_nsec = (timer->ms % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    if (timer->callback != NULL) {
        timer->callback();
    }

    free(timer); 

    return;
}

void _ntInstallTimer(void(*callback)(), float seconds) {
    _ntInitCores();

    // allocate timer
    struct bi_timer *timer = (struct bi_timer *)malloc(sizeof(struct bi_timer));

    // convert seconds to milliseconds
    timer->ms = (unsigned long long)((unsigned long long)(seconds * 1000.f));

    // set callback
    timer->callback = callback;

    // create job
    _ntRequestCoreJob(_nt_timer_thread, timer);
}