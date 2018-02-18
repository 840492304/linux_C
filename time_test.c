//
// Created by Wen on 2018/2/5.
//

#include <time.h>
#include <stdio.h>
void main(){

    struct tm * tm_pr;
    time_t * tmt_pr;
    time_t  tmt_pr2;

    *tmt_pr = time(tmt_pr);

    printf("%f", *tmt_pr);
   // printf("%12.12s",  localtime(tm_pr) +4 );

}