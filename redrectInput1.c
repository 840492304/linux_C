//
// Created by Wen on 2018/3/5.
//  标准输入的重定向的第一种方法  close(0) then open
//

#include <stdio.h>
#include <zconf.h>
#include <fcntl.h>


void main(){

    char  input[100];

    fgets(input, 100, stdin);

    printf("%s", input);

    //关闭标准输入 文件描述符0（终端）被关闭了，新打开一个文件，会获取 最小的通道 ，即这个0 ，变成标准输入
    close(0);

    if(open("/etc/passwd", O_RDONLY) != 0){

        perror("/etc/passwd 文件打开失败");
    }

    fgets(input, 100, stdin);
    printf("%s", input);
    fgets(input, 100, stdin);
    printf("%s", input);

  //  return 1;

}