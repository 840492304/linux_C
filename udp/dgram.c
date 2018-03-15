//
// Created by Wen on 2018/3/15.
//
/**
 * 封装udp的函数
 */
#include <netdb.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 1234
#define WEB_NAME "wen.com"

#define oops(m, n) {perror(m); exit(n);}

int make_server_addr(int port, struct sockaddr_in * saddr){

    struct hostent *hp;
    hp = gethostbyname(WEB_NAME);
    bzero((void *) saddr, sizeof(saddr));

    if (hp == NULL) return  -1;

    bcopy((void *) hp->h_addr, (void *) &saddr->sin_addr, hp->h_length);

    saddr->sin_port   = htons(port);
    saddr->sin_family = PF_INET;

    return 0;
}

/**
 *
 * @param port
 * @return  socket_id
 */

int make_server_udp(int port){

    struct  sockaddr_in addr_in;
    int socket_id;

    int res;

    socket_id = socket(PF_INET, SOCK_DGRAM, 0);

    if (socket_id == -1) oops("申请socket出错", 1);

    res = make_server_addr(port, &addr_in);

    if(res == -1) oops("建立addr出错", 2);

    if(bind(socket_id, (struct sockaddr *) &addr_in, sizeof(addr_in)) == -1) oops("bind出错", 3);

    return  socket_id;
}



int make_client_udp(int port){


    return socket(PF_INET, SOCK_DGRAM, 0);
}


/**
 *  转换sockaddr_in中的数据
 * @param host
 * @param len
 * @param prot_p
 * @param saddr_in
 * @return
 */
int get_internet_address(char * host, int len, int * prot_p, struct sockaddr_in * saddr_in){


    strncpy(host, inet_ntoa(saddr_in->sin_addr), len);//十进制转换成字符串的IP地址

    * prot_p  = ntohs(saddr_in->sin_port);            //

    return 0;
}