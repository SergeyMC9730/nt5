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

#include <nt5emul/ntcore.h>

#include <stdlib.h>
#include <string.h>

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

    size_t cores = NT_CORES_MAXIMUM;
    size_t size = sizeof(struct ntcore) * cores;

    // allocate array for cores
    nt_cores = (struct ntcore *)malloc(size); // 4 nt cores

    // cleanup array
    memset(nt_cores, 0, size);

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
    
    size_t cores = NT_CORES_MAXIMUM;

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
    return nt_cores[id % NT_CORES_MAXIMUM].executes_job;
}

#include <stdio.h>

void _ntDumpCores() {
    size_t cores = NT_CORES_MAXIMUM;

    for (size_t i = 0; i < cores; i++) {
        struct ntcore *core = nt_cores + i;

        printf("core(%zu): job:%d\n", i, core->executes_job);
    }
}