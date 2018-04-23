//
// Created by Wen on 2018/4/23.
//
#include "stdio.h"
#define MAXLINE 4
int main(int ac, char *av[]) {


    char buf[MAXLINE];

    while (fgets(buf, MAXLINE,  stdin) != NULL) {
        printf("---\n");
        if (fputs(buf, stdout) == EOF) {

            printf("fputs错误\n");
        }
        printf("\n");
    }


    return 0;
}