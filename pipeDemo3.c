//
// Created by Wen on 2018/3/6.
//

/**
 *  实现 | 的功能
 *
 * 父进程传给子进程 ，管道

 *
 */


#include <unistd.h>
#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>


#define oops(m, n) {perror(m); exit(n);}

int main(int ac, char *av[]) {

    int  pi[2], pid;

    if (ac != 3) {
        oops("参数错误", 1);
    }


    if (pipe(pi) != 0) {
        oops("pipe失败", 2);
    }


    //可以fork了

    if ((pid = fork())== -1) {
        oops("fork出错啦", 1);
    }

    /**
     * 子进程接受参数
     */
    if (pid == 0) {

        dup2(pi[0], STDIN_FILENO);
        close(pi[0]);
        close(pi[1]);

        /**
         * 现在只有万事俱备了
         */
        execlp(av[2], av[2], NULL);

        oops(av[2], 3);
    }else{

        /**
         * 主进程负责发送数据到管道
         */

        dup2(pi[1], STDOUT_FILENO);
        close(pi[1]);
        close(pi[0]);

        execlp(av[1], av[1], NULL);
        oops(av[1], 4);
    };

    return 0;
}