//
// Created by 郑泽超 on 2018/1/2.
//


#include "lock.h"
#include <stdio.h>
#include <unistd.h>
int main(){

    int sid = initReadWriteLock(888,2,1);
    printf("读者%d申请读资源\n",getpid());



    lock(sid,READ);
    printf("read 进入临界\n");
    sleep(10);
    printf("read 退出临界\n");
    unlock(sid,READ);



}