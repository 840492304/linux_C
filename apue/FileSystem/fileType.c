//
// Created by Wen on 2018/4/19.
//

#include <sys/stat.h>
#include "apue.h"

/**
 * 文件类型
 */

int main(int ac, char *av[]) {


    struct stat buf;

    for (int i = 1; i < ac; i++) {

        if (lstat(av[i], &buf) == -1) {
            printf("获取文件%s信息失败 \n", av[i]);
            continue;
        }

        if (S_ISBLK(buf.st_mode)) {
            printf("%s is block special  \n", av[i]);
        } else if (S_ISCHR(buf.st_mode)) {
            printf("%s is char special  \n", av[i]);
        } else if (S_ISDIR(buf.st_mode)) {
            printf("%s is dir  \n", av[i]);
        }else if (S_ISFIFO(buf.st_mode)) {
            printf("%s is S_ISFIFO  \n", av[i]);
        }else if (S_ISREG(buf.st_mode)) {
            printf("%s is regular file  \n", av[i]);
        }

    }


    return 0;
}