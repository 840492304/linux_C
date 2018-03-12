//
// Created by Wen on 2018/3/12.
//

#include <zconf.h>
#include "socketLib.h"

void connect_handler(int fd);

 int main(int ac, char *av[]) {

    struct  response res;

    res = make_socket_client();

     if (res.code == -1) {

         perror("创建client错误\n");
         printf("创建client错误:%s", res.msg);

         exit(1);
     }


    connect_handler(res.socket_id);

    close(res.socket_id);

    return 0;
}


void connect_handler(int fd){

    char buf[1024];
    int read_num;

    while ((read_num = read(fd, buf, 1024)) > 0){

        write(1, buf, read_num);
    }

}