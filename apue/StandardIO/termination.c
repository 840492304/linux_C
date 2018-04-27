//
// Created by Wen on 2018/4/27.
//

#include <zconf.h>

/***
 *
 *  如果 子进程和 父进程同时 都在main里面return，那么终止状态是啥
 *
 *   父进程的返回状态
 *
 */

int main(int ac, char *av[]) {

    int pid;

    if ((pid = fork()) > 0) {

        return 2;
    }
    sleep(1);

    return 3;

    return 0;
}