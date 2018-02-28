//
// Created by Wen on 2018/2/28.
//sleep()实现原理

#include <stdio.h>
#include <signal.h>
#include <zconf.h>

void main(){

    void  wakeUpHandle(int);
    /**
     * 先注册一下处理函数
     */
    signal(SIGALRM, wakeUpHandle);

    alarm(2);

    pause();

    printf("ending ....");
}
void  wakeUpHandle(int var){


    printf("%d\n", var);

}