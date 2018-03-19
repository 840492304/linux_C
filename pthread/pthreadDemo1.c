//
// Created by Wen on 2018/3/19.
//

#include <stdio.h>
#include <pthread.h>

void * print(void * msg);
int main(int ac, char *av[]) {

    pthread_t p1, p2;

    char *msg1, *msg2;

    pthread_create(&p1, NULL, print, (void *) "heihei");
    pthread_create(&p2, NULL, print, (void *) "haha");

    pthread_join(p1, &msg1);
    pthread_join(p2, &msg2);

    printf("ending ....");
    printf("%s \n", msg1);
    printf("%s \n", msg2);


    return 0;
}


void * print(void * msg){

    char * s;

    s = (char * ) msg;

    for (int i = 0; i <5 ; ++i) {

        printf("%s\n", s);
    }

    return (void *) "------";
}