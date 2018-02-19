//
// Created by Wen on 2018/2/3.
//

#include "stdio.h"
#define PAGE_LEN 24
#define LINE_LEN 512

void do_more(FILE *);

int see_more();


int main(int ac, char * av[]){
    system("stty -icanon");

    FILE * fp;
    if (ac == 1) {
        do_more(stdin);
    } else{
       // while (--ac);
        if ((fp = fopen(*++av, "r")) != NULL) {
            do_more( fp);
            fclose(fp);
        }else{
            exit(1);
        }

    }

    return 0;
}

void do_more(FILE * fp){


    char line[LINE_LEN];

    int num_of_line = 0;

    int  replay;

    while (fgets(line, LINE_LEN, fp)){

       // printf("num_of_line is %d , page len is %d \n", num_of_line, PAGE_LEN);

        if (num_of_line == PAGE_LEN) {

            replay = see_more();

            if (replay == 0) {
                break;
            }
            num_of_line -= replay ;

        }

        if (fputs(line, stdout) == EOF) {
            exit(1);
        }

        num_of_line++;
    }
}


int see_more(){
    FILE * tty;

    //防止被重定向
    tty = fopen("/dev/tty", "r");
    if (tty == NULL) {

        exit(1);
    }

    int c;
    printf("more?");

    while ((c = getc(tty))){

        if (c =='q') {
            return 0;
        }else if(c == ' '){
            return  PAGE_LEN;
        }else if(c == '\n'){
            return 1;
        }

    }

    return 0;
}