//
// Created by Wen on 2018/4/16.
//
#include <fcntl.h>
#include "apue.h"

int main(int ac, char *av[]) {

    int flag ;

    if (ac != 2) {
        err_quit("参数个数错误!\n");
    }

    if ( ( flag =  fcntl(atoi(av[1]), F_GETFL)) == -1) {

        err_quit("获取flag错误\n");
    }

    /**
     * 这三者只能设置其中的一个
     */
    switch ( flag & O_ACCMODE) {

        case O_RDONLY:
            printf("O_RDONLY\n");
            break;
        case O_WRONLY:
            printf("O_WRONLY\n");
            break;
        case O_RDWR:
            printf("O_RDWR\n");
            break;
        default:
            printf(".....");
    }

    if (flag & O_APPEND) {

        printf("追加\n");
    }
    if (flag & O_NONBLOCK) {
        printf("非阻塞\n");
    }
    if (flag & O_SYNC){
        printf("同步");
    }



    return 0;
}