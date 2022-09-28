// linux 进程间通信共享内存sample

#include <sys/ipc.h>
#include <sys/shm.h>

// ftok - convert a pathname and a project identifier to a System V IPC key
#include <sys/types.h>
#include <sys/ipc.h>

#include "shmdata.h"
#include <stdio.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <fcntl.h> 
#include <sys/stat.h>
#include <semaphore.h>

static sem_t *sem_w;
static sem_t *sem_r;

int main() {
    int is_running = 1;
    void *shm = NULL;
    struct shared_use_st *shared;
    int shmid;
    char buffer[MSG_BUFFER_SIZE] = {0};

    sem_w = sem_open(SEMPATH_W, O_EXCL);
    if (sem_w == NULL) {
        printf("sem_open failed\n");
        printf("Error: %s\n", strerror(errno));
        return errno;
    }

    sem_r = sem_open(SEMPATH_R, O_EXCL);
    if (sem_r == NULL) {
        printf("sem_open failed\n");
        return errno;
    }

    // 创建 IPC key
    key_t ipc_key = ftok("./send", 121);
    if (ipc_key < 0) {
        printf("ipc key created failed\n");
        return errno;
    }

    shmid = shmget(ipc_key, sizeof(struct shared_use_st), 0600);
    if (shmid < 0) {
        printf("shared memory create failed\n");
        return errno;
    }

    shm = shmat(shmid, NULL, 0);
    if (shm == (void *)-1) {
        printf("shmat attatch memory failed\n");
        return errno;
    }

    shared = (struct shared_use_st *)shm;
    // 可写
    // shared->written = 0;
    while (is_running)
    {
        // 可读
        //if (shared->written == 1)
        sem_wait(sem_r);
        {
            printf("receive:%s\n", shared->msg);
            
            //sleep(1);
            if (0 == strncmp(shared->msg, "end", 3)) {
                is_running = 0;
            }

            // 可写
            //shared->written = 0;
            sem_post(sem_w);
        }
    }

    if (shmdt(shm) == -1) {
        printf("shmdt()  detaches the shared memory segment failed\n");
        return errno;
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        printf("hmctl(IPC_RMID) failed\n");
        return errno;
    }

    return 0;
