//
// Created by Wen on 2018/3/9.
//

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <netdb.h>
#include <ctype.h>
#include <zconf.h>

#define SOCKET_PORT 12002

/**
 * ls   socket 服务器端
 * @param ac
 * @param av
 * @return
 */
#define oops(m, n) {perror(m); exit(n);}
#define BUFFSIZE 255

void deal_input_dirname(char * dirname);

int main(int ac, char *av[]) {

    int socket_id;
    struct sockaddr_in server_in;
    int client_fd;

    struct hostent * hp;

    char comnand[BUFFSIZE];
    FILE * exec_fp_read;//进程ID

    FILE * client_fp_read;
    FILE * client_fp_write;

    char dirName[BUFFSIZE];


    int c;

    socket_id = socket(AF_INET, SOCK_STREAM, 0);


    if (socket_id == -1) {
        oops("socket创建失败", 1);
    }


    /**
     * bind
     */
    bzero((void *) & server_in, sizeof(server_in));

    if((hp = gethostbyname("wen.com")) == NULL){
        oops("IP地址获取失败", 2);
    }

    bcopy((void *) hp->h_addr, (void *) &server_in.sin_addr, sizeof(hp->h_addr));

    server_in.sin_port   = htons(SOCKET_PORT);
    server_in.sin_family = AF_INET;

   if(bind(socket_id, (struct sockaddr *) &server_in, sizeof(server_in)) == -1){
       oops("绑定socket失败", 2);
   }

   /**
    * listen
    */
    if (  listen(socket_id, 2) == -1) {
        oops("listen出错", 3);
    }

    while (1) {

        client_fd = accept(socket_id, NULL, NULL);

        if (client_fd == -1) {
            oops("accept出错", 3);
        }

        /**
         * 获取客户端输入
         */
        if((client_fp_read = fdopen(client_fd, "r")) == NULL){
            oops("accept出错", 3);
        }

        /**
         * 获取到输入的文件夹
         */
        if (fgets(dirName, BUFFSIZE - 5, client_fp_read) == NULL) {
            oops("gets出错", 3);
        }


        deal_input_dirname(dirName);

        sprintf(comnand, "ls %s", dirName);

        /**
         * 打印客户端 的文件夹
         */
        write(1, comnand, strlen(comnand));


        /**
         *  popen()  pclose关闭
         */
        if ((exec_fp_read = popen(comnand,  "r")) == NULL) {

            oops("打开命令行进程出错", 3);
        }

        /**
         * 写入client的文件描述符
         */
      if ((client_fp_write = fdopen(client_fd, "w")) == NULL) {

            oops("client_fpw出错", 3);
        }

        while ((c = getc(exec_fp_read)) != EOF) {

            putc(c, client_fp_write);
        }

        pclose(exec_fp_read);    //popen  pclose

        fclose(client_fp_write);    //关闭流
        fclose(client_fp_read);

        close(client_fd);  //关闭客户端文件描述符
    }

    return 0;
}

/**
 *
 * @param dirname
 */
void deal_input_dirname(char * dirname){

    char * temple , *res;

    res = temple = dirname;

    for (; *temple ; ++temple) {

        if ((*temple) == '/' || isalnum(* temple)) {

            *res++ = *temple;
        }
    }

    *res = '\0';

}
