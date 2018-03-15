//
// Created by Wen on 2018/3/13.
//

#include <zconf.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "socketLib.h"

#define REQUEST_SIZE 1024

void read_til_ctrnl(FILE * fp);
void  process_request(char * request_str, int fd);

void cant_do(int fd);

bool not_exist(char arg[1024]);

bool is_dir(char *arg);

void do_ls(int fd, char *dirname);

bool ends_in_cgi(char *arg);

char * file_type(char * str);

void do_exec(char *arg, int fd);

void do_cat(char *arg, int fd);

int main(int ac, char *av[]) {

    int socket_id, client_fd;

    struct response res;
    char res_str[100];

    char request[REQUEST_SIZE];

    int num;

    FILE * fp_in, *fp_out;

    res = create_socket_server();

    if (res.code == -1) {

        perror("创建socket服务器失败");
        exit(1);
    }

    socket_id = res.socket_id;

  //  while (1) {

        client_fd = accept(socket_id, NULL, NULL);

        if (client_fd == -1) {

            sprintf(res_str, "accept失败了哦");
            write(1, res_str, strlen(res_str));
            //sizeof(res_str);
        }

        fp_in = fdopen(client_fd, "r");

        fgets(request, REQUEST_SIZE, fp_in);

        printf("当前请求为:%s\n", request);

        read_til_ctrnl(fp_in);

        /**
         * 处理请求
         */
        process_request(request, client_fd);

//    }


    return 0;
}

/**
 * 读取其余剩下的所有信息，直到结束
 * @param fp
 */
void read_til_ctrnl(FILE * fp) {

    char buf[1024];

    while (fgets(buf, 1024, fp) != NULL && strcmp(buf, "\r\n") != 0);

}


/**
 * 未找到
 * @param fd
 * @param arg
 */
void not_found(int fd, char * arg){

    FILE * fp_out = fdopen(fd, "w");
    fprintf(fp_out, "HTTP/1.0 404 Not found\r\n");
    fprintf(fp_out, "Content-type:text/plain\r\n");
    fprintf(fp_out, "\r\n");
    fprintf(fp_out, "404not found%s", arg);

    fclose(fp_out);


}

/**
 * 请求处理
 * @param request_str
 * @param fd
 */
void  process_request(char * request_str, int fd){

    char cmd[100], arg[1024];

    char str[255];

    if (fork() != 0) {
        return;
    }

    /**
     * 加上前缀
     */
    strcpy(arg, "./");
    if((sscanf(request_str, "%s%s", cmd, arg + 2)) != 2){

        sprintf(str, "当前参数个数不对");
        write(fd, str, strlen(str));
        close(fd);

        return ;
    }

    if (strcmp(cmd, "GET") != 0) {

        cant_do(fd);

    } else if(not_exist(arg)){

        not_found(fd, arg);

    } else if(is_dir(arg)){

        do_ls(fd, arg);

    } else if(ends_in_cgi(arg)){

        do_exec(arg, fd);

    } else{
        do_cat(arg, fd);
    }


}

void do_cat(char *arg, int fd) {

    char * type = file_type(arg);

    char * content = "text/plain";

    char c;

    FILE * fpsocket, * fpfile;


    if (strcmp(type, "html") == 0) {
        content = "html";
    } else if (strcmp(type, "gif") == 0) {
        content = "image/gif";
    } else if (strcmp(type, "jpg") == 0) {
        content = "image/jpeg";
    } else if (strcmp(type, "jpeg") == 0) {
        content = "image/jpeg";
    }

    fpsocket = fdopen(fd, "w");

    fpfile = fopen(arg, "r");

    if (fpfile != NULL && fpsocket != NULL) {

        set_head(fpsocket, content);

        set_head(fpsocket, "\r\n");

        while ((c = getc(fpfile) != NULL)){

            putc(c, fpsocket);
        }

        fclose(fpfile);
        fclose(fpsocket);
    }

    exit(0);
}

void do_exec(char *arg, int fd) {

    FILE * fp;

    fp = fdopen(fd, "w");

    dup2(fp, 1);
    dup2(fp, 2);
    close(fp);

    execl(arg, arg, NULL);

    perror(arg);
}

bool ends_in_cgi(char *arg) {
    struct stat info;


    return (strcmp(file_type(arg), "cgi") == 0);
}


char * file_type(char * str){

    char *p ;

    if ((p =strrchr(str, '.') ) != NULL) {

        return p + 1;
    }

    return "";
}


void set_head(FILE *fp, char *content){

    fprintf(fp, "HTTP/1.0 200 OK\r\n");

    if (content) {
        fprintf(fp, "Content-type:%s\r\n", content);
    }
}



void do_ls(int fd, char *dirname) {
    FILE * fp;

    fp = fdopen(fd, "w");

    set_head(fp, "text/plain");

    fprintf(fp, "\r\n");

    fflush(fp);

    dup2(fd, 1);
    dup2(fd, 2);

    close(fd);
    execlp("ls", "ls", "-l", dirname, NULL);

    perror(dirname);

    exit(1);
}

bool is_dir(char *arg) {
    struct stat info;

    return (stat(arg, &info) == -1 && S_ISDIR(info.st_mode)) ;
}

/**
 * 判断文件或者命令是否存在
 * @param arg
 * @return
 */
bool not_exist(char * arg) {

    struct stat info;

    return stat(arg, &info) == -1;
}

/**
 *
 * @param fd
 */
void cant_do(int fd) {

//    char str[255];
//    sprintf(str, "当前方法不支持");
//    write(fd, str, strlen(str));
//    close(fd);

      FILE * fp_out = fdopen(fd, "w");
      fprintf(fp_out, "HTTP/1.0 503 Not Implmented\r\n");
      fprintf(fp_out, "Content-type:text/plain\r\n");
      fprintf(fp_out, "\r\n");
      fprintf(fp_out, "方法不被支持");

      fclose(fp_out);
}

















