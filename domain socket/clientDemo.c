//
// Created by Wen on 2018/3/19.
//

#include <sys/un.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define  SOCKET "/tmp/socketdemo"

#define oops(m, n) {perror(m); exit(n);}

int main(int ac, char *av[]) {

    struct sockaddr_un addr;
    int socket_id;
    int add_len;

    char msg[] = "this is a test domain socket\n";

    socket_id = socket(PF_UNIX, SOCK_DGRAM, 0);

    if (socket_id == -1) oops("socKet申请失败", 1);


    /**
     * 初始化socket addr
     */
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET);

    add_len = sizeof(addr.sun_family) + strlen(addr.sun_path);  //为什么是这样

    if(sendto(socket_id, msg, strlen(msg), 0, (struct sockaddr *) &addr, add_len) == -1){

        oops("发送失败", 1);

    }


    return 0;
}