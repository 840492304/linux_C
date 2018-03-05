//
// Created by Wen on 2018/3/5.
// open close dup() colse
//
/**
 * 跟close open  的区别在于一个先close 再open,一个是open后再close
 *
 * dup会复制一个当前的文件描述符到目前还在空缺的文件描述符上去
 *
 * dup2会关闭  arg2的文件描述符
 */

#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>


void main(){


    char  input[100];

    fgets(input, 100, stdin);

    printf("%s", input);

    int fd = open("/etc/passwd", O_RDONLY);

//    close(0);
//    dup(fd);
    /**
     * 或者
     */
    dup2(fd, 0);

    close(fd);

    printf("%d\n", fd);

    fgets(input, 100, stdin);
    printf("%s", input);
    fgets(input, 100, stdin);
    printf("%s", input);
    fgets(input, 100, stdin);
    printf("%s", input);

}
