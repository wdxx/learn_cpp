#ifndef _SHMDATA_H_
#define _SHMDATA_H_

#define MSG_BUFFER_SIZE 4096
#define SEMPATH_W "/sem_w"
#define SEMPATH_R "/sem_r"

struct  shared_use_st
{
    int written;
    char msg[MSG_BUFFER_SIZE];
    /* data */
};
