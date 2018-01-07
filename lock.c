//
// Created by 郑泽超 on 2018/1/3.
//


#include "semaphore.h"
#include "lock.h"
int lock(int semid,int semnum){


    struct sembuf sem;

    sem.sem_num = 2;
    sem.sem_flg = SEM_UNDO;
    int waiter;
    if(semnum == READ){
        //获取读锁
        //核心：每次读者在尝试获取锁的时候都要去检查是否有写者在等待


        //检查写者是否有等待的

        sem.sem_op = -1;
        sem.sem_num = WAITERFLAGPREVENT;
        P(semid,sem);

        waiter = getSemaphoreValue(semid,WRITERWAITING);





        if(waiter != 0){  //有写者在等待 则把自己阻塞,等待之前的写者全部处理完毕

            sem.sem_op = 1;
            V(semid,sem);//先释放临界区


            sem.sem_op = -1;
            sem.sem_num = FLAG;
            P(semid,sem);
        }




            //没有写进程在等待
            sem.sem_op = 1;
            V(semid, sem);//先释放临界区
            struct sembuf rsem;

            rsem.sem_num = READ;
            rsem.sem_flg = SEM_UNDO;
            rsem.sem_op = -1;
            //准备获取一个读锁


            for (;;) {//不断自旋测试


                P(semid, rsem);

                //获取WAITERFLAG保护临界区
                sem.sem_op = -1;
                sem.sem_num = WAITERFLAGPREVENT;
                P(semid, sem);

                waiter = getSemaphoreValue(semid, WRITERWAITING);


                //核心：每次读者在尝试获取锁的时候都要去检查是否有写者在等待


                if (waiter == 0) {  //有写者在等待 则把自己阻塞,等待之前的写者全部处理完毕

                    sem.sem_op = 1;
                    V(semid, sem);//释放临界区
                    break;
                } else {



                    //有写者在等待 释放该读锁 等待重新获取


                    rsem.sem_op = 1;
                    rsem.sem_num = READ;
                    V(semid, rsem);
                    sem.sem_op = 1;
                    V(semid, sem);//释放临界区

                    rsem.sem_op = -1;
                    rsem.sem_num = READ;
                }


            }
            // 自旋 保证在唤醒过程中不会有其他写进程进入 而造成错误的结果


















    } else{
        //获取写锁

        //同步更新wait_writer


        sem.sem_op = -1;
        sem.sem_num = WAITERFLAGPREVENT;
        P(semid,sem);

        sem.sem_op = 1;
        sem.sem_num = WRITERWAITING;
        V(semid,sem);//wait_writer++

        sem.sem_num = WAITERFLAGPREVENT;
        sem.sem_op = 1;
        V(semid,sem);





        struct sembuf rsem;
        rsem.sem_num = READ;
        rsem.sem_flg = SEM_UNDO;
        rsem.sem_op = -TOTALREADER;

        //获取全部读锁 如果能获取到 说明没有读进程 否则等待读进程退出
        P(semid,rsem);

        //获取成功
        struct sembuf wsem;
        wsem.sem_num = WRITE;
        wsem.sem_flg = SEM_UNDO;
        wsem.sem_op = -1;
        P(semid,wsem);//获取写锁

        //获取成功 则把该写者从等待写者队列中移除


        sem.sem_op = -1;
        sem.sem_num = WAITERFLAGPREVENT;
        P(semid,sem);

        sem.sem_op = -1;
        sem.sem_num = WRITERWAITING;
        P(semid,sem);//wait_writer+--

        sem.sem_num = WAITERFLAGPREVENT;
        sem.sem_op = 1;
        V(semid,sem);





  //      rsem.sem_op = TOTALREADER;

//        V(semid,rsem);

    }


}


int unlock(int semid,int semnum){
    struct sembuf sem;

    sem.sem_flg = SEM_UNDO;

    if(semnum == READ){

        sem.sem_num = READ;
        sem.sem_op = 1;

        V(semid,sem);





    } else{


        //写锁释放

        sem.sem_op = -1;
        sem.sem_num = WAITERFLAGPREVENT;
        P(semid,sem);

        int ret =getSemaphoreValue(semid,WRITERWAITING);//获取当前还在等待的写锁

        //避免在判断过程中 有写锁进入等待 需要同步
        if (ret == 0){
            //将flag置位1
            sem.sem_num = FLAG;
            sem.sem_op = 1;
            V(semid,sem);
        }

        sem.sem_num = WAITERFLAGPREVENT;
        sem.sem_op = 1;

        V(semid,sem);


        //释放读锁
        sem.sem_num = READ;
        sem.sem_op = TOTALREADER;
        V(semid,sem);

        //释放写锁
        sem.sem_num = WRITE;
        sem.sem_op = 1;
        V(semid,sem);




    }




}


int initReadWriteLock(key_t key,int readers,int writers){
    int a[5] = {readers,writers,0,0,1};
    return initSemaphore(key,5,a);

}

int destoryReadWriteLock(int semid){
    deleteSemaphore(semid,2);
}