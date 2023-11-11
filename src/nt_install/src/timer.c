#include <pthread.h>

#include <raylib.h>

typedef struct bi_timer_t {
    unsigned long long ms;

    void (*callback)();
} bi_timer_t;

#include <time.h>
#include <errno.h> 

void *_bi_timer_thread(bi_timer_t *timer) {
    struct timespec ts;
    int res;

    if (timer->ms < 0)
    {
        errno = EINVAL;
        return (void *)1;
    }

    ts.tv_sec = timer->ms / 1000;
    ts.tv_nsec = (timer->ms % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    timer->callback();

    MemFree(timer); 

    return (void *)0;
}

void _boot_install_timer(void(*callback)(), float seconds) {
    bi_timer_t *timer = (bi_timer_t *)MemAlloc(sizeof(bi_timer_t));

    timer->ms = (unsigned long long)((unsigned long long)(seconds * 1000.f));
    timer->callback = callback;

    pthread_t thread;

    pthread_create(&thread, NULL, &_bi_timer_thread, timer);
}