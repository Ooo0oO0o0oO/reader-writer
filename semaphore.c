//
// Created by 郑泽超 on 2018/1/2.
//

#include <sys/ipc.h>
#include<errno.h>
#include <stdio.h>
#include "semaphore.h"

int initSemaphore(key_t key,int semn,int *val){
    int status=0,semid;                    //信号量标识符semid
    if ((semid=semget(key,semn,0x600|IPC_CREAT|IPC_EXCL))==-1)
    {
        if (errno==EEXIST)               //EEXIST：信号量集已经存在，无法创建
            semid=semget(key,semn,0);      //创建一个信号量
    }
    else
    {


        int *temp = val;

        for(int i = 0;i<semn;i++){
            semun arg;
            arg.val = val[i];//信号量的初值

            status = semctl(semid,i,SETVAL,arg);//设置信号量集中的一个单独的信号量的值。
            temp--;
        }


    }
    if (semid==-1||status==-1)
    {
        perror("initsem failed");
        return(-1);
    }
    /*all ok*/
    return(semid);
}



int deleteSemaphore(int semid,int semnum){

    if((semctl(semid,semnum,IPC_RMID))<0)   //删除进程Ad的信号量值，IPC_RMID是删除命令
    {
        perror("semctl error");
        return 0;
    }

    return 1;


}


int getSemaphoreValue(int semid,int semnum){
    int val;                      //信号量的初值
    val = semctl(semid,semnum,GETVAL,0);      //设置信号量集中的一个单独的信号量的值。
    return val;
}
int P(int semid,struct  sembuf buf){

//    buf.sem_op = -1;
//    buf.sem_num = 0;
//    buf.sem_flg = SEM_UNDO;

    if(semop(semid,&buf,1) == -1){
        /*操作失败*/
        perror("semop P failed\n");
        return 0;
    }

    return 1;



}



int V(int semid, struct  sembuf buf){

//    buf.sem_op = 1;
//    buf.sem_num = 0;
//    buf.sem_flg = SEM_UNDO;

    if(semop(semid,&buf,1) == -1){
        /*操作失败*/
        perror("semop V failed\n");
        return 0;
    }

    return 1;



}