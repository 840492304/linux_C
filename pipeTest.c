//
// Created by Wen on 2018/3/6.
//
#include <zconf.h>
#include <string.h>
#include <stdio.h>

/**
 * 将pi[0]  重定向到标准输出上，我想的是这样，当通道有数据发送的时候，它将会自动read，然后输出。哈哈，事实上是不行的，管道输出端,并不能打印显示出数据
 *
 * @param ac
 * @param av
 * @return
 */
int main(int ac, char *av[]) {

    char * str = "rdftgyuhijhg\n";

    int len = strlen(str);

    char get[len];

    int pi[2];
    pipe(pi);

    while (1) {

        dup2(pi[0], STDOUT_FILENO); //
        // dup2(pi[1], STDOUT_FILENO);
        printf("fghj");
        write(pi[1],str, len);
        read(STDOUT_FILENO, get, len);
        sleep(1);
    }




    return 0;
}