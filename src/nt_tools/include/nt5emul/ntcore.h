#include <pthread.h>

#include <stdbool.h>

struct ntcore {
    bool executes_job;
    
    void *argument;
    
    pthread_t thread;
    pthread_cond_t cond;
    pthread_mutex_t mutex;

    void (*job)(struct ntcore core, void *argument);
};

void _ntInitCores();
void _ntRequestCoreJob(void (*job)(struct ntcore core, void *argument), void *arg);
bool _ntCoreBusy(size_t id);