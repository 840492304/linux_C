//
// Created by Wen on 2018/3/5.
//
/**
 * 文件描述符属于进程的属性
 *  fork exec时都会保留这些属性
 */
#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <fcntl.h>

void main(){

    int pid = 0, fd;

    printf("接下来表演的是如何将子进程的文件描述符1重定向\n");

    /**
     * fork子进程
     */
    if ((pid == fork()) == -1) {
        perror("fork出错啦");
        exit(1);
    }


    /**
     * 这是子进程
     */
    if (pid == 0) {

        close(1); //关闭

        creat("a", 0666);

        execlp("who", "who", NULL);

        exit(1);

    }


    if (pid != 0) {

        wait(NULL);
        printf("over!");
    }

}