//
// Created by Wen on 2018/4/26.
//
#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>

int main(int ac, char *av[]) {

    char  buf[1024];
//    char  buf2[1024];
    int c;

    FILE * fp_a;
//    FILE * fp_b;

    fp_a = fopen("./a.txt", "r");
    /**
     * 设置为NBUF
     */
   // if (setvbuf(fp_a, NULL, _IONBF, NULL) != 0) {
  //  if (setvbuf(fp_a, buf, _IOLBF, 1024) != 0) {
    if (setvbuf(fp_a, buf, _IOFBF, 1024) != 0) {

        printf("fp_a设置"
                       "缓冲错误");
        return 1;
    }

//    fp_b = fopen("b.txt", "r+");
//    /**
//     * 设置为行缓冲
//     */
//
//    if (setvbuf(fp_b, buf, _IOLBF, 1024 ) != 0) {
//        perror("");
//        printf("fp_b设置行缓冲错误");
//        return 1;
//    }


    /**
     * 从a中获取到数据
     *
     */
    putc(72, stdout);
    putc(72, stdout);
    putc(72, stdout);

    c = getc(fp_a);
   // fflush(fp_b);

    putc(c, stdout);

    sleep(10);

    printf("over\n");

    return 0;
}
