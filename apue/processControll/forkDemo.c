//
// Created by Wen on 2018/4/25.
//

#include <zconf.h>
#include <stdlib.h>
#include "stdio.h"

int main(int ac, char *av[]) {


    int pid ;
    int status;

    if((pid = fork()) > 0){

        pid = fork();

        if (pid == 0) {
            sleep(3);
            printf("我的ppid是%d \n", getppid());
            exit(0);
        }

        printf("First child process die\n");
        exit(0);
    }


    wait(&status);
    printf("main  die\n");

    return 0;
}