#include <nt5emul/bi/ntcore.h>

#include <raylib.h>

ntcore_t *nt_cores = NULL;

#include <nt5emul/boot_install_settings.h>

void *_biCoreJob(void *arg) {
    ntcore_t *core = (ntcore_t *)arg;

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

void _biInitCores() {
    if (nt_cores != NULL) return; // we dont want to init them twice

    size_t cores = NT_CORES;

    // allocate array for cores
    nt_cores = (ntcore_t *)MemAlloc(sizeof(ntcore_t) * cores); // 4 nt cores

    for (size_t i = 0; i < cores; i++) {
        // create condition and mutex
        pthread_cond_init(&nt_cores[i].cond, NULL);
        pthread_mutex_init(&nt_cores[i].mutex, NULL);

        // create thread
        pthread_create(&nt_cores[i].thread, NULL, &_biCoreJob, &nt_cores[i].executes_job);
    }
}

void _biRequestCoreJob(void (*job)(struct ntcore_t core, void *argument), void *arg) {
    bool request_acomplished = false;
    
    size_t cores = NT_CORES;

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

bool _biCoreBusy(size_t id) {
    return nt_cores[id % NT_CORES].executes_job;
}