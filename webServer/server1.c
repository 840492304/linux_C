//
// Created by Wen on 2018/3/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <zconf.h>
#include <string.h>
#include "socketLib.h"

void response_handle(int fd);

int main(int ac, char *av[]) {

    struct response res;
    int client_fd;

    res = create_socket_server();

    if (res.code == -1) {

        printf("%s", res.msg);

        exit(1);
    }

    while (1) {

        client_fd = accept(res.socket_id, NULL, NULL);

        if (client_fd == -1) {

            printf("accept error");
            exit(1);
        }


        write(client_fd, "now Time is :", strlen("now Time is :"));

        response_handle(client_fd);

        close(client_fd);
    }


    return 0;
}

void response_handle(int fd){

    char * timestamp ;
    time_t now;

    time(&now);
    timestamp = ctime(&now);

    write(fd, timestamp, strlen(timestamp));
}


