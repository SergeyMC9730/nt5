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

#include <stdbool.h>

struct ntcore {
    bool executes_job;
    
    void *argument;
    
    pthread_t thread;
    pthread_cond_t cond;
    pthread_mutex_t mutex;

    void (*job)(struct ntcore core, void *argument);
};

#define NT_CORES_MAXIMUM 16

void _ntInitCores();
void _ntRequestCoreJob(void (*job)(struct ntcore core, void *argument), void *arg);
bool _ntCoreBusy(size_t id);

// prints state of all cores
void _ntDumpCores();