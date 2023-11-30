#include <pthread.h>

#include <raylib.h>

#include <nt5emul/bi/ntcore.h>

#include <nt5emul/bi/timer.h>

typedef struct bi_timer_t {
    unsigned long long ms;

    void (*callback)();
} bi_timer_t;

#include <time.h>
#include <errno.h> 

void _bi_timer_thread(ntcore_t core, void *arg) {
    bi_timer_t *timer = (bi_timer_t *)arg;

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

    MemFree(timer); 

    return;
}

void _boot_install_timer(void(*callback)(), float seconds) {
    _biInitCores();

    // allocate timer
    bi_timer_t *timer = (bi_timer_t *)MemAlloc(sizeof(bi_timer_t));

    timer->ms = (unsigned long long)((unsigned long long)(seconds * 1000.f));

    timer->callback = callback;

    // create job
    _biRequestCoreJob(_bi_timer_thread, timer);
}