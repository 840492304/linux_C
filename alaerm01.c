//
// Created by Wen on 2018/3/1.
//
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <sys/time.h>

void handle(int sys);
int set_my_clock(int u_msecs);

int main(){

    signal(SIGALRM, handle);

//
//    printf("%d", set_my_clock(200));

    if ( set_my_clock(500) == -1) {

        perror("定时器出错了");
        exit(1);
    }

    while(1){

        pause();
    }


}
/**
 * 输入的是毫秒
 * @param u_msecs
 */
int set_my_clock(int u_msecs){

    long sec   = u_msecs/1000;
    int u_sec = (u_msecs%1000)*1000;
    struct itimerval time_struct;

    time_struct.it_value.tv_sec = sec;
    time_struct.it_value.tv_usec = u_sec;

    time_struct.it_interval.tv_sec  = sec;
    time_struct.it_interval.tv_usec = u_sec;


    return  setitimer(ITIMER_REAL, &time_struct, NULL);
}




void handle(int sys){

    static  int time = 10;

    time--;

    if (time <=0 ) {

        printf("byeBye...\n");
        exit(0);
    } else{

        printf("倒计时...%d\n", time);
    }

}