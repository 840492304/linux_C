//
// Created by Wen on 2018/5/28.
//

#include <apue.h>
#include <pthread.h>

void * threadFun1(void * arg){

    printf("thread 1 arg :%s \n", (char *)arg);
    printf("thread 1 returning\n");
    return (void *)1;
}
void * threadFun2(void * arg){

    printf("thread 2 arg :%s \n", (char *)arg);
    printf("thread 2 returning\n");
    return (void *)2;
}


int main(int ac, char *av[]) {

    pthread_t pid1,pid2;
    int reNo;

    void * rval_ptr;

    if ((reNo = pthread_create(&pid1, NULL, threadFun1, "test")) != 0) {
        err_sys("创建线程1失败\n");
    }

    pthread_join(pid1, &rval_ptr);
    printf("线程1 退出码为 %ld\n", (long) rval_ptr);


    if ((reNo = pthread_create(&pid2, NULL, threadFun2, "test2")) != 0) {
        err_sys("创建线程2失败\n");
    }

    pthread_join(pid2, &rval_ptr);
    printf("线程2 退出码为 %ld\n", (long) rval_ptr);


    return 0;
}