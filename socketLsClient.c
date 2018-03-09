//
// Created by Wen on 2018/3/9.
//


#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <strings.h>
#include <zconf.h>

#define oops(m, n) {perror(m); exit(n);}
#define BUFFSIZE 255

#define SOCETPORT 12002
/**
 * rls socket实现ls 的客户端
 * @param ac
 * @param av
 * @return
 */
int main(int ac, char *av[]) {

    int socket_id;
    struct hostent	*hp ;
    int server_fd;
    long receive_num;

    char buf[BUFFSIZE];

    struct sockaddr_in  serveraddr_t;

    if (ac != 3) {

        oops("参数输入错误", 2);
    }

    if ((socket_id = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        oops("socket创建失败", 1);
    };

    if ((hp = gethostbyname("wen.com")) == NULL) {
        oops("获取IP地址失败", 3);
    }

    bzero((void *)&serveraddr_t, sizeof(serveraddr_t));

    bcopy((void *) hp->h_addr, (void *) & serveraddr_t.sin_addr, sizeof(hp->h_addr_list));

    serveraddr_t.sin_family = AF_INET;
    serveraddr_t.sin_port   = htons(SOCETPORT);


    if ((connect(socket_id, (struct sockaddr *) &serveraddr_t, sizeof(serveraddr_t))) == -1) {
        oops("socket连接失败", 4);
    }

    /**
     *开始给服务器写入数据
     */

    if (write(socket_id, av[2], strlen(av[2])) == -1) {
        oops("给服务器写入路径失败", 5);
    }

    /**
     * 添加换行
     */
    if (write(socket_id, "\n", strlen("\n")) == -1) {
        oops("给服务器写入路径失败", 5);
    }

    /**
     * 循环读取数据
     */

    while( (receive_num =  read(socket_id, buf, BUFFSIZE)) > 0){

        if (write(1, buf, receive_num) == -1) {

            oops("打印失败", 5);
        }
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

