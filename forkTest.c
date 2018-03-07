//
// Created by Wen on 2018/3/7.
//

#include <zconf.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char *av[]) {


    if (fork() != 0) {

        exit(0);
    }

    for (int i = 0; i < 5; ++i) {

        printf("this is backing");
        sleep(2);

    }

    return 0;
}