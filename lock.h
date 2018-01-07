//
// Created by 郑泽超 on 2018/1/3.
//

#ifndef FINALPRO_LOCK_H
#define FINALPRO_LOCK_H

#include <sys/types.h>
#include <sys/sem.h>
#define READ 0
#define WRITE 1
#define WAITERFLAGPREVENT 4
#define WRITERWAITING 2
#define FLAG 3
#define TOTALREADER 2

int lock(int semid,int semnum);

int unlock(int semid,int semnum);


int initReadWriteLock(key_t key,int readers,int writers);

int destoryReadWriteLock(int semid);
#endif //FINALPRO_LOCK_H
