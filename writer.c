#include<stdio.h>
#include<unistd.h>
#include "lock.h"
int main() {
    int sid = initReadWriteLock(888,2,1);


    printf("写者%d申请写资源\n",getpid());



    lock(sid,WRITE);
    printf("write 进入临界\n");

    sleep(10);

    printf("write 退出临界\n");
    unlock(sid,WRITE);








   // destoryReadWriteLock(sid);
}

//https://www.cnblogs.com/LZYY/p/3453582.html
//https://www.classes.cs.uchicago.edu/archive/2017/winter/51081-1/LabFAQ/lab7/Semaphores.html
//https://www.cs.umd.edu/~hollings/cs412/s96/synch/