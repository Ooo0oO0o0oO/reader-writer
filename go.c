//
// Created by 郑泽超 on 2018/1/7.
//



#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>
int main(){

    srand( (unsigned)time( NULL ) );
    int i = 0;
/* Display 10 numbers. */
    for( ; i < 8;i++) {
        int s = rand();





        if (s % 4 == 0){
            printf("创建writer\n");


            if(fork() == 0){
                if(execl("./main","main",NULL)<0){
                    perror("创建writer失败");
                }
            }
        }else{
            printf("创建reader\n");
            if(fork() == 0) {

                if(execl("./reader","reader",NULL)<0){
                    perror("创建reader失败");
                }

            }
        }

    }

    int wpid = -1;
    int status = 0;
    while ((wpid = wait(&status)) > 0);

    printf("删除信号量\n");
    system("sudo ipcrm -S 0x00000378");


}