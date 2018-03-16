
/**
 * recvfrom(socket_id, buf, BUFFSIZE, 0,  &saddr_in_receve, &addr_len)
 *
 * 这个长度。。。int * 类型的
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <memory.h>
#include "dgram.h"

#define BUFFSIZE 1024

#define oops(m, n) {perror(m); exit(n);}

int main(int ac, char *av[]) {

    char buf[BUFFSIZE];
    int rece_num;

    int addr_len;

    int socket_id;
    struct sockaddr_in saddr_in;
    struct sockaddr_in saddr_in_receve;
    if(ac != 3) oops("参数有误", 1);

    /**
     *
     */
    if ((socket_id = make_server_udp(4445)) == -1) oops("socket申请失败", 2);


    printf("socket%d\n", socket_id);

    if ( make_server_addr(atoi(av[1]), &saddr_in) == -1) oops("地址失败", 3);

    if (sendto(socket_id, av[2], strlen(av[2]), 0, (struct sockaddr *) &saddr_in, sizeof(saddr_in)) == -1) {

        //printf("发送失败");
        perror("发送失败");

        return 1;
    }

    printf("发送成功!等待接收中\n");

    addr_len = sizeof(saddr_in_receve);

    if((rece_num = recvfrom(socket_id, buf, BUFFSIZE, 0,  &saddr_in_receve, &addr_len)) > 0){

        buf[rece_num] = '\0';
        printf("接收到数据为:%s", buf);
    }

    printf("%d\n", socket_id);

    return 0;
}