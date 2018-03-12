//
// Created by Wen on 2018/3/12.
//

#ifndef SOCKE_LIB_H
#define SOCKE_LIB_H

#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

#include "socketLib.h"

#define SERVER_URL "wen.com"
#define PORT       12000


struct response {
    int  code ;
    char *msg;
    int socket_id;
};


struct response make_response(int code, char *msg, int socket_id);
struct sockaddr_in  make_sockaddr();
struct response create_socket_server();

struct response make_socket_client();




/**
 * 创建一个 socket服务器
 *
 * @return
 */
struct response create_socket_server() {

    int socket_id;
    struct sockaddr_in server_addr;

    socket_id = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_id == -1) {

        return make_response( -1, "创建socket失败", NULL);
    }

    server_addr = make_sockaddr();

    /**
     * 绑定
     */
    if (bind(socket_id, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {

        perror("绑定失败。。");
        return make_response(-1, "绑定失败", NULL);
    }

    /**
     * 监听
     */
    if (listen(socket_id, 100) == -1) {

        return make_response(-1, "Listen失败", NULL);
    }

   return make_response(0, "创建socket服务器成功!", socket_id);
}


/**
 * 创建一个socket客户端
 * @return
 */
struct response make_socket_client() {

    int socket_id;
    struct sockaddr_in server_addr;

    int fd;

    socket_id = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_id == -1) {

        return make_response( -1, "创建socket失败", NULL);
    }

    server_addr = make_sockaddr();

    fd = connect(socket_id, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if (fd == -1) {
        return make_response( -1, "连接失败", NULL);
    };


    return make_response( 0, "创建成功", socket_id);
}

/**
 * 获取addr
 * @return
 */
struct sockaddr_in make_sockaddr(){

    struct sockaddr_in server_addr;
    struct hostent	* hp;

    bzero((void *) &server_addr, sizeof(server_addr));

    hp = gethostbyname(SERVER_URL);

    if (hp == NULL) {
        printf("-----");
        exit(1);
    }

    bcopy((void *) hp->h_addr ,(struct sockaddr *)&server_addr.sin_addr, sizeof(hp->h_addr));


    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(PORT);

    return server_addr;
}


/**
 *   创建一个响应
 * @param code
 * @param msg
 * @return
 */

struct response make_response(int code, char *msg, int socket_id){

    struct response res;

    res.code = code;
    res.msg  = msg;

    if (socket_id != NULL) {
        res.socket_id = socket_id;
    }

    return res;
}





#endif
