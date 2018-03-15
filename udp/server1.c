//
// Created by Wen on 2018/3/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "dgram.h"

#define oops(m, n) {perror(m); exit(n);}
#define BUFFSIZE 1024



int main(int ac, char *av[]) {

    int port , addr_len;
    int socket_id;
    int receve_num;
    struct sockaddr_in saddr_in;

    char buf[BUFFSIZE];

    if (ac != 2 ) {
        oops("参数个数不对", 1);
    }

    if ((port = atoi(av[1])) <= 0) {
        oops("端口号不对", 1);
    }

    socket_id = make_server_udp(port);

   // make_server_addr(port, &saddr_in);

    addr_len = sizeof(saddr_in);


    while (1) {


        if((receve_num = recvfrom(socket_id, buf, BUFFSIZE, 0,  &saddr_in,  &addr_len)) > 0){


            printf("-----接受----");

            buf[receve_num] = '\0';

            printf("接收到数据为:%s", buf);

            print_client(&saddr_in);

        }


    }



    printf("结束");

    return 0;
}


void print_client(struct sockaddr_in  * saddr){

    char host[BUFFSIZE];
    int port;

    get_internet_address(host, BUFFSIZE, &port, saddr);

    printf("当前客户端 IP为 %s 当前端口为 %d\n", host, port);

}




