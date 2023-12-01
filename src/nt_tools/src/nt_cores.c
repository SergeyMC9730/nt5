#include <nt5emul/ntcore.h>

#include <stdlib.h>

struct ntcore *nt_cores = NULL;

void *_ntCoreJob(void *arg) {
    struct ntcore *core = (struct ntcore *)arg;

    do {
        // lock mutex
        pthread_mutex_lock(&core->mutex);

        // wait for a job
        pthread_cond_wait(&core->cond, &core->mutex);
        
        // execute it
        core->executes_job = true;
        core->job(core[0], core->argument);

        core->executes_job = false;

        // unlock mutex
        pthread_mutex_unlock(&core->mutex);
    } while (true);

    return NULL;
}

void _ntInitCores() {
    if (nt_cores != NULL) return; // we dont want to init them twice

    size_t cores = 16;

    // allocate array for cores
    nt_cores = (struct ntcore *)malloc(sizeof(struct ntcore) * cores); // 4 nt cores

    for (size_t i = 0; i < cores; i++) {
        // create condition and mutex
        pthread_cond_init(&nt_cores[i].cond, NULL);
        pthread_mutex_init(&nt_cores[i].mutex, NULL);

        // create thread
        pthread_create(&nt_cores[i].thread, NULL, &_ntCoreJob, &nt_cores[i].executes_job);
    }
}

void _ntRequestCoreJob(void (*job)(struct ntcore core, void *argument), void *arg) {
    bool request_acomplished = false;
    
    size_t cores = 16;

    do {
        for (size_t i = 0; i < cores; i++) {
            // if core doesn't do anything give him a job
            if (!nt_cores[i].executes_job) {
                nt_cores[i].job = job;
                nt_cores[i].argument = arg;
                
                // raise condition signal
                pthread_cond_signal(&nt_cores[i].cond);

                return;
            }
        }
    } while (true);
}

bool _ntCoreBusy(size_t id) {
    return nt_cores[id % 16].executes_job;
}