//
// Created by Wen on 2018/2/26.
//


#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char * av[]){

    int flags ;

    int get_char ;

    int res;

    int fd = open("/dev/ttys000", O_RDWR );


    if (fd == -1) {

        perror("can not open");

        exit(1);

    }

    flags = fcntl(fd, F_GETFL);

    if (flags == -1) {

        perror("get flag error");

        exit(1);

    }

    flags = flags | O_SYNC;

    res = fcntl(fd, F_SETFL, flags);

    if (res == -1) {

        printf("set error");
        exit(1);
    }

    printf("is open ");


    while((get_char = getchar()) != 'q'){

        printf("%c is %d\n", get_char, get_char);
    }


}

