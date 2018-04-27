//
// Created by Wen on 2018/4/27.
//
//对标准 I/O 流是否进行冲洗，这取决于实现.
#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>

int main(int ac, char *av[]) {


    putchar(70);

   // _exit(0); //不输出
    exit(0); //输出
    return 0;
}