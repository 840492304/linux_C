//
// Created by Wen on 2018/4/16.
//
/**
 * 编写一个与 3.12 节中 dup2 功能相同的函数，要求不调用 fcntl 函数，并且要有正确的出
 *   错处理
 */

/**
 * dup2 的实现
 * @param ac
 * @param av
 * @return
 */

#include <apue.h>

int mydup2(int fd1, int fd2);

int main(int ac, char *av[]) {

    if (ac != 3) {
        err_sys("参数个数错误");
        return -1;
    }

    if (mydup2(atoi(av[1]), atoi(av[2])) == -1) {

        err_sys("mydup2出错啦");
    }

    printf("成功~~~~\n");

    return 0;
}

int mydup2(int fd1, int fd2){

    int temple[FOPEN_MAX];
    int fd;
    int cur = 0;

    if (fd2 < 0 || fd2 > FOPEN_MAX) {
        return -1;
    }

    if (fd1 == fd2) {
       return 0;
    }

    while ((fd = dup(fd1)) < fd2) {

        if (fd == -1) {
            err_sys("dup出错");
        }

        temple[cur++] = fd;
    }

    /**
     * 关闭多复制了的
     */
    for (int i = 0; i < cur; ++i) {

        if (close(temple[i]) == -1) {
            err_sys("colse出错");
        }
    }

    return 0;
}