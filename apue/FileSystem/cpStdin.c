//
// Created by Wen on 2018/4/23.
//

//getc()跟fgetc()区别是，getc是宏

#include "apue.h"

int main(int ac, char *av[]) {

    int temp;
    while ((temp = getc(stdin)) != EOF) {

        if (putc(temp, stdout) == EOF) {
            err_sys("putc错误");
        }
    }

    if (ferror(stdin)) {
        err_sys("错误");
    }

    return 0;
}
