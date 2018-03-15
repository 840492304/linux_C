//
// Created by Wen on 2018/3/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <memory.h>
#include "dgram.h"

#define oops(m, n) {perror(m); exit(n);}


int main(int ac, char *av[]) {

    int socket_id;
    struct sockaddr_in saddr_in;

    if(ac != 3) oops("参数有误", 1);

    if ((socket_id = make_client_udp(atoi(av[1]))) == -1) oops("socket申请失败", 2);

    if ( make_server_addr(atoi(av[1]), &saddr_in) == -1) oops("地址失败", 3);

    if (sendto(socket_id, av[2], strlen(av[2]), 0, (struct sockaddr *) &saddr_in, sizeof(saddr_in)) == -1) {

        printf("发送失败");

        return 1;
    }

    printf("发送成功!");

    return 0;
}