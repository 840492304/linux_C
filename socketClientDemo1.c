//
// Created by Wen on 2018/3/8.
//

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <zconf.h>

#define BUFFSIZE 255


#define oops(m, n) {perror(m); exit(n);}
/**
 * socket client demo
 * @param ac
 * @param av
 * @return
 */
int main(int ac, char *av[]) {

    int socket_id;
    struct hostent *hp;

    struct sockaddr_in addr_in;
    char buf[BUFFSIZE];

    if (ac != 3) {

        oops("请重新输入参数", 1);
    }

    /**
     * 先申请一个socket
     */

    socket_id = socket(PF_INET, SOCK_STREAM, 0);

    if (socket_id == -1) {

        oops("申请socket失败", 2);
    }


    /**
     *  serverName
     */
    hp = gethostbyname(av[1]);

    if (hp == NULL) {
        oops("服务器IP地址获取失败", 2);
    }

    bzero(&addr_in, sizeof(addr_in));
    bcopy((void *)hp->h_addr, (void *) &addr_in, sizeof(hp->h_addr));
    addr_in.sin_port   = htons(atoi(av[2]));
    addr_in.sin_family = AF_INET;

    if(connect(socket_id, (struct sockaddr *) &addr_in, sizeof(addr_in)) == -1){

        oops("连接失败", 2);
    }

    /**
     * 读取失败
     */
    if(read(socket_id, buf, BUFFSIZE) == -1){

        oops("未获取到数据", 3);
    }

    write(1, buf, strlen(buf));

    close(socket_id);

    return 0;
}