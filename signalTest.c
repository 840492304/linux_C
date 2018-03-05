//
// Created by Wen on 2018/3/2.
//
#include <signal.h>
#include <stdio.h>

void handler(int action_number, struct __siginfo *  siginfo, void* p);

int main(){

    struct  sigaction new_siga_struct;

    struct __siginfo siginfo;

    sigset_t block;

    sigemptyset(&block);
    sigaddset(&block, SIGQUIT);

    /**
     * 处理方法
     */
    new_siga_struct.__sigaction_u.__sa_sigaction = handler;

    new_siga_struct.sa_flags = SA_RESTART | SA_RESETHAND;

    new_siga_struct.sa_mask  = block;

    sigaction(SIGINT, &new_siga_struct, NULL);

    while(1){


    }



}


void handler(int action_number, struct __siginfo *  siginfo, void * p){


    printf("------");
    printf("$s", siginfo->si_status);
    printf("$s", siginfo->si_value);

}