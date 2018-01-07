#include<stdio.h>
#include<stdlib.h>

int main(){
    for(int i = 0;i<3;i++){
        if(fork() == 0){
            printf("f\n");
            exit(0);
        }
    }
}
