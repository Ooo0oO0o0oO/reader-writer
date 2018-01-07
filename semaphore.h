//
// Created by 郑泽超 on 2018/1/2.
//

#ifndef FINALPRO_SEMAPHORE_H
#define FINALPRO_SEMAPHORE_H
#include <sys/types.h>
#include <sys/sem.h>
typedef union _semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
} semun;
/*初始化信号量*/
int initSemaphore(key_t key,int semn,int *val);


/*P 操作*/

int P(int semid, struct sembuf sem);

/* V操作*/
int V(int semid, struct sembuf sem);



int getSemaphoreValue(int semid,int semnum);
/*删除信号量*/

int deleteSemaphore(int semid,int semnum);
#endif //FINALPRO_SEMAPHORE_H
