//
// Created by Wen on 2018/4/16.
//
/**
 * 如果使用追加标志打开一个文件以便读、写，能否仍用 lseek 在任一位置开始读？能否用
    lseek 更新文件中任一部分的数据？请编写一段程序验证

    lseek能影响读取，但是影响不了写入
 */

#include <apue.h>
#include <fcntl.h>
#include "stdio.h"

int main(int ac, char *av[]) {

    int fd;
    char buf[5];
    fd = open("test.txt", O_RDWR | O_APPEND);

    if (fd == -1) {
        printf("打开出错\n");
        exit(1);
    }

    if (lseek(fd, 5, SEEK_SET) == -1) {
        printf("lseek出错\n");
        exit(1);
    }

    //先读看看
    read(fd, buf, 5);
    printf("先读看看:");
    printf("%s\n", buf);

    printf("再写入试试:");
    if ( write(fd, "------", strlen("------")) == -1) {
        printf("写入失败，哈哈哈哈\n");
        exit(1);
    }
    printf("写入成功，哈哈哈哈\n");

    /**
     * 添加
     */

    return 0;
}