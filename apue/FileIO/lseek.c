//
// Created by Wen on 2018/4/12.
//

#include <zconf.h>
#include "apue.h"
#include "stdio.h"

int main(int ac, char *av[]) {

    int64_t offset = lseek(STDIN_FILENO, 0, SEEK_CUR);
    if(offset != -1){

        printf("can not use lseek\n");
        printf("%d", offset);
    } else{

        printf("yes\n");
        printf("%d", offset);
    }


    return 0;
}