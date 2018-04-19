//
// Created by Wen on 2018/4/19.
// umask 掩码，就是创建屏蔽字, 创建文件的时候，默认是没得执行权限的，文件夹有执行权限，文件或者文件夹的最终权限 等于creat 或者open函数的权限与上屏蔽字的补码
#include "apue.h"
#include "fcntl.h"

#define RWRWRW (S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH)

int main(int ac, char *av[]) {

    umask(0);

    if (creat("A", RWRWRW) == -1) {
        err_sys("创建a失败\n");
    }

    umask(S_IRGRP | S_IWGRP| S_IROTH | S_IWOTH);

    if (creat("B", RWRWRW) == -1) {
        err_sys("创建B失败\n");
    }

    return 0;
}