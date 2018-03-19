//
// Created by Wen on 2018/3/19.
//

#include <sys/un.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <zconf.h>

#define  SOCKET "/tmp/socketdemo"
#define  BUFF_SIZE 1024

#define oops(m, n) {perror(m); exit(n);}

int main(int ac, char *av[]) {

    struct sockaddr_un addr;
    int socket_id;
    int add_len;
    char buf[BUFF_SIZE];

    int len ;

    socket_id = socket(PF_UNIX, SOCK_DGRAM, 0);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET);

    add_len = strlen(SOCKET) + sizeof(addr.sun_family);

    if (bind(socket_id, (struct sockaddr *) &addr, add_len) == -1) oops("bind 失败", 1);


    while (1) {

        len = read(socket_id, buf, BUFF_SIZE);

        if (len == -1) {

            oops("read 失败了\n", 2);
        }

        buf[len] = '\n';

        printf("当前收到的消息为:%s\n", buf);
    }


    return 0;
}