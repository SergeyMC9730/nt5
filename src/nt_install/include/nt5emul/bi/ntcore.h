#include <pthread.h>

#include <stdbool.h>

typedef struct ntcore_t {
    bool executes_job;
    
    void *argument;
    
    pthread_t thread;
    pthread_cond_t cond;
    pthread_mutex_t mutex;

    void (*job)(struct ntcore_t core, void *argument);
} ntcore_t;

void _biInitCores();
void _biRequestCoreJob(void (*job)(struct ntcore_t core, void *argument), void *arg);
bool _biCoreBusy(size_t id);