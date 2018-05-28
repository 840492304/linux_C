//
// Created by Wen on 2018/5/28.
//

#include "apue.h"
#include <pthread.h>

pthread_t pid;


void * threadFun(void * arg){

    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("当前线程的pid为%d, 线程id为%d \n", pid, (int)tid);

    return (void *)0;
}

int main(int ac, char *av[]) {

    int returnNo;
    pid_t pid;

    if(returnNo = pthread_create(&pid, NULL, threadFun, NULL) != 0){

        err_sys("创建线程失败");
    }

    sleep(2);

    pid = getpid();
    printf("主线程的pid为%d,\n", pid);

    return 0;
}