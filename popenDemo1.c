//
// Created by Wen on 2018/3/7.
//

#include <stdio.h>
#include <zconf.h>
#include <fcntl.h>

int main(int ac, char *av[]) {

    char buf[100];

    FILE *fp  = popen("ls | more", "r");

    /**
     * 注意fgets
     */
    while (fgets(buf, 100, fp) != NULL){

        printf("%s", buf);
    }

    pclose(fp);

    return 0;
}