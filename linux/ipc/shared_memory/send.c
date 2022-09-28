// linux 进程间通信共享内存sample

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// ftok - convert a pathname and a project identifier to a System V IPC key
#include <sys/types.h>
#include <sys/ipc.h>

#include "shmdata.h"
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
    char buf[MSG_BUFFER_SIZE + 1];

    sem_w = sem_open(SEMPATH_W, O_CREAT|O_EXCL, 0600, 1);
    if (sem_w == NULL) {
        printf("sem_open failed\n");
       printf("Error: %s\n", strerror(errno));
        return errno;
    }

    sem_r = sem_open(SEMPATH_R, O_CREAT|O_EXCL, 0600, 0);
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

    shmid = shmget(ipc_key, sizeof(struct shared_use_st), 0666|IPC_CREAT);
    if (shmid < 0) {
        printf("shared memory create failed\n");
        printf("Error: %s\n", strerror(errno));
        return errno;
    }

    shm = shmat(shmid, (void*)0, 0);
    if (shm == (void *)-1) {
        printf("shmat attatch memory failed\n");
        return errno;
    }

    printf("shm = %x\n", shm);

    memset(shm, 0, sizeof(struct shared_use_st));
    shared = (struct shared_use_st *)shm;

    // 可写
    //shared->written = 0;
    while (is_running)
    {
        /*
        while (shared->written == 1)
        {
            sleep(1);
            printf("Wait for sending ...\n");
        }*/
        sem_wait(sem_w);

        printf("send msg:");
        if (NULL == fgets(buf, MSG_BUFFER_SIZE, stdin)) {
            printf("fgets fialed\n");
            return -1;
        }

        strncpy(shared->msg, buf, MSG_BUFFER_SIZE);

        // 可读
        //shared->written = 1;
        sem_post(sem_r);

        if (0 == strncmp(buf, "end", 3)) {
            is_running = 0;
            sem_wait(sem_w);
        }
    }

    if (shmdt(shm) == -1) {
        printf("shmdt()  detaches the shared memory segment failed\n");
        return errno;
    }

    sem_close(sem_r);
    sem_close(sem_w);
    sem_unlink(SEMPATH_R);
    sem_unlink(SEMPATH_W);

    return 0;
}
