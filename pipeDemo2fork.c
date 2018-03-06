//
// Created by Wen on 2018/3/6.
//

/**
 * pipe是阻塞型的，   跟golang的无缓冲的管道 是一样的
 */

#include <zconf.h>
#include <stdio.h>
#include <string.h>


#define inputs "werftyguhi\n"
/**
 * 使用fork
 */
void main(){

    int pi[2], pid, len;

    char gets[100];

    if(pipe(pi) != 0){

        perror("pipe出错");
    }


    pid = fork();

    printf("pid is %d \n", pid);
    printf("pipe文件描述符  为 %d %d \n", pi[0], pi[1]);

    len = strlen(inputs);

    if (pid == 0) {

        close(pi[0]);
        while (1){


            /**
             * pipe管道发送数据
             */
            if (write(pi[1], inputs, len) != len) {

                printf("出错啦");
            }

            sleep(5);
        }
    }


    if (pid != 0) {
        close(pi[1]);

        while (1){


//        /**
//         * 读取管道数据
//         */
            read(pi[0], gets, len);
//
//        /**
//         * 发送给标准输出
//         */
            write(1, gets, len);

            for (int i= 0; i < len; ++i) {

                gets[i] = 'x';
            }


         //   printf("%s", inputs);

            sleep(2);

        }
    }





}

