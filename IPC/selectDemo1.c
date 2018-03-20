//
// Created by Wen on 2018/3/20.
//


#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <ntsid.h>
#include <unistd.h>

#define oops(m, n) {perror(m); exit(n);}

void show_read(int fd, char * filename);
int main(int ac, char *av[]) {

    struct timeval timeout;
    int fd1, fd2, maxfd;
    char * file_name1, *file_name2;
    int res;
    fd_set  read_fd;

    if(ac != 4) oops("参数错误", 1);

    file_name1 = av[1];
    file_name2 = av[2];


    if(fd1 = open(file_name1, O_RDONLY) == -1) oops(file_name1, 2);
    if(fd2 = open(file_name2, O_RDONLY) == -1) oops(file_name2, 2);

    maxfd = fd2 + 1;

    while (1) {

        FD_ZERO(&read_fd);
        FD_SET(fd1, &read_fd);
        FD_SET(fd2, &read_fd);

        timeout.tv_sec  = atoi(av[3]);
        timeout.tv_usec = 0;

        res = select(maxfd, &read_fd, NULL, NULL, &timeout);

        if ( res == -1)  oops("select 出错", 2);

        if (res > 0) {

            if (FD_ISSET(fd1, &read_fd)) {
                show_read(fd1, file_name1);
            }

            if (FD_ISSET(fd1, &read_fd)) {
                show_read(fd2, file_name2);
            }

        } else{

            printf("等待输入中.....\n");
        }

    }


    return 0;
}


void show_read(int fd, char * filename){

    char buf[1024];
    int read_len;
    printf("%s输人:", filename);

    if ((read_len = read(fd, buf, 1024)) == -1) oops("读取出错", 1);

    buf[read_len] = '\0';

    printf("%s\n:", buf);

    fflush(stdout);

}
















