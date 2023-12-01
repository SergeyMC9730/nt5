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

    if (timer->ms < 0)
    {
        errno = EINVAL;
        return;
    }

    ts.tv_sec = timer->ms / 1000;
    ts.tv_nsec = (timer->ms % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    timer->callback();

    free(timer); 

    return;
}

void _ntInstallTimer(void(*callback)(), float seconds) {
    _ntInitCores();

    // allocate timer
    struct bi_timer *timer = (struct bi_timer *)malloc(sizeof(struct bi_timer));

    timer->ms = (unsigned long long)((unsigned long long)(seconds * 1000.f));

    timer->callback = callback;

    // create job
    _ntRequestCoreJob(_nt_timer_thread, timer);
}