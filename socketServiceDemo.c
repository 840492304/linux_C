//
// Created by Wen on 2018/3/8.
//
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <zconf.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>
#include <time.h>

#define oops(m, n) {perror(m); exit(n);}
#define HOSTLEN 255
#define PORTNUM 11000
/**
 * socket 服务器的一个demo
 * @param ac
 * @param av
 * @return
 */
int main(int ac, char *av[]) {

    FILE * socket_fp;
    int accept_fd;
    int socket_id;
    struct sockaddr_in saddr;
    struct hostent * hp;
    char hostname[HOSTLEN] = {0};
    time_t time_now;


    /**
     *   向系统申请一个socket
     *
     *   PF_INET  ip v4协议
     *
     *      SOCK_STREAM 可靠的 byte streams
     *      SOCK_DGRAM dgram : datagram 数据报  ，不可靠的
     *      SOCK_RAW   super_user  才能用的:sockets provide access to internal network protocols and inter-
     faces
     *
     *
     */
    socket_id = socket(PF_INET, SOCK_STREAM, 0);

    if (socket_id == -1) {
        oops("socket 申请失败", 1);
    }

    /**
     * 初始化
     */
    bzero((void *)&saddr, sizeof(saddr));

//    char * loc = "localhost";
//
//    sethostname(loc, strlen(loc)); //
//
//    gethostname(hostname, HOSTLEN);

    /**
     * 获取到host的一些内容
     */
    hp = gethostbyname("wen.com");  //如果采用sethostname()函数的话，返回的是'Wen' MacBook Pro'local' ?这个值是来自哪里的哦

    if (hp == NULL) {
        oops("gethostbyname错误", 1);
    }

    bcopy((void *)hp->h_addr, (void *) &saddr.sin_addr, hp->h_length);
    saddr.sin_port   = htons(PORTNUM);
    saddr.sin_family = AF_INET;

    if (bind(socket_id, (struct sockaddr * ) &saddr, sizeof(saddr)) != 0) {

        oops("绑定出错啦", 2);
    }
    /**
     * listen(socket_id, backlog)
     *
     * backlog: 连接队列的长度
     *
     * 如果超长客户端会接收到ECONNREFUSED错误：if  the underlying protocol supports retransmission, the request may be ignored so that retries may succeed.（如果底层协议支持重传，则可以忽略该请求，以便重试可以成功）
     */
    if (listen(socket_id, 100) != 0) {
        oops("监听出错啦", 3);
    }

    while (1){

        /**
         * 阻塞
         */
        accept_fd = accept(socket_id, NULL, NULL);

        printf("嘿嘿，我接收到了");

        if (accept_fd == -1) {
            oops("接受出错", 3);
        }

        /**
         * 写入数据
         */
        socket_fp = fdopen(accept_fd, "w");

        if (socket_fp == NULL) {

            oops("socket_fp", 4);
        }

        time_now = time(NULL);

        fprintf(socket_fp, "%s", ctime(&time_now));
        fprintf(socket_fp, "-----end-----" );

        fclose(socket_fp);

    }

    return 0;
}

