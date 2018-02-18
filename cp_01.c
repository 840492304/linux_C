//
// Created by Wen on 2018/2/6.
//
/**
 * 复制文件的流程:  打开 open 源文件 获取文件描述符 -> 创建create 目标文件 获取文件描述符->read读取源文件的内容 获得已经
 * 被填充内容buffer ，返回读取的字节数 -> 写入数据 write ->循环读取写入完毕 ->关闭文件
 *
 *  疑问？fcntl.h 里面装的是啥？
 *          unistd.h 装的又是啥？
 *
 *          尽快熟悉这两个头文件里面的内容~~~~~
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


//定义每次读取字节数已经创建文件的权限
#define BUFFER_SIZE 2048
#define COPY_MODE   0440

void oops(char * str1, char * str2);

void main(int ac , char * av[]){

    int cmd, source_fd, target_fd, readed_size;
    char buffer[BUFFER_SIZE];

    /**
     * 判断输入参数个数是否正常
     */

    if (ac !=  3) {

        oops("参数个数不对",  " ");
    }

    /**
     * 打开打开源文件
     */
    if (( source_fd = open(av[1], O_RDONLY)) == -1) {

        oops("cant open source file", av[1]);
    }

    /**
     * 创建目标文件
     */
    if ((target_fd = creat(av[2], COPY_MODE)) == -1) {

        oops("cant create target file", av[2]);
    }

    /**
     * 读取数据
     */
    while ((readed_size = read(source_fd, buffer, BUFFER_SIZE)) > 0) {

        if (write(target_fd, buffer, readed_size) != readed_size) {
            oops("复制文件出错啦", av[2]);
        }

    }

    /**
     * 数据读出异常
     */
    if (readed_size == -1) {
        oops("读取文件出错啦", av[1]);
    }

    /**
     * 关闭文件
     */

    if (close(source_fd) == -1 || close(target_fd) == -1) {
        oops("关闭文件出错", " ");
    }

    return;
}

/**
 * 打印错误~~~~
 * @param str1
 * @param str2
 */
void oops(char * str1, char * str2){

    fprintf(stderr, "oops ! error is %s \n", str1);
    perror(str2);
    exit(1);
}