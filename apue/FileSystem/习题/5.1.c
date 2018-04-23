//
// Created by Wen on 2018/4/23.
//
#include "apue.h"

int main(int ac, char *av[]) {

    return 0;
}

int mySetBuf(FILE * fp, char * buf){

    if (buf == NULL) {
        return setvbuf(fp, _IONBF, NULL, NULL);
    }

    //_IOLBF _IOFBF皆可
    return setvbuf(fp, NULL, _IOLBF, BUFSIZ);
}