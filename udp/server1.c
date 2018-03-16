//
// Created by Wen on 2018/3/15.
//

/**
 * recvfrom(socket_id, buf, BUFFSIZE, 0,  &saddr_in_receve, &addr_len)
 *
 * 这个长度。。。int * 类型的
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>

#include "dgram.h"

#define oops(m, n) {perror(m); exit(n);}
#define BUFFSIZE 1024

void send_to_client(char * msg, int socked_id, struct sockaddr_in *adrr);

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

    printf("监听端口号为%d\n", port);
    printf("socket_id为%d\n", socket_id);

    addr_len = sizeof(saddr_in);

    while (1){

        if((receve_num = recvfrom(socket_id, buf, BUFFSIZE, 0,  &saddr_in,  &addr_len)) > 0){

            buf[receve_num] = '\0';

            printf("接收到数据为:%s", buf);

            print_client(&saddr_in);

            send_to_client(buf, socket_id, &saddr_in);

            printf("发送完毕\n");


        }
    }

    printf("结束\n");

    return 0;
}


void print_client(struct sockaddr_in  * saddr){

    char host[BUFFSIZE];
    int port;

    get_internet_address(host, BUFFSIZE, &port, saddr);

    printf("当前客户端 IP为 %s 当前端口为 %d\n", host, port);



}


void send_to_client(char * msg, int socked_id, struct sockaddr_in *adrr){

    char res[1024];
    int send_num;

    sprintf(res, "I has received your msg:%s\n", msg);

  //  if ( make_server_addr(4445, adrr) == -1) oops("地址失败", 3);

    if ((send_num = sendto(socked_id, res, sizeof( res), 0, adrr, sizeof(adrr)))  <= 0){

        oops("返回信息错误", 3);
    }else{

        printf("发送完毕1\n");
    }

}


