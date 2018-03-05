//
// Created by Wen on 2018/3/5.
//设置当前进程的接受异步IO
//
#include <fcntl.h>
#include <zconf.h>
#include <signal.h>

#include <aio.h>
#include <stdio.h>

/**
 * 通过设置O_ASYNC
 * @return
 */
int set_IO_async(){

    int flags ;

    //设置当前进程接受SIGIO信号
    // Set the process or process group to receive SIGIO and SIGURG signals; process groups are specified by supplying arg as negative, otherwise arg is interpreted as a process ID.
    fcntl(0, F_SETOWN, getpid());

    //获取当前flags
    flags = fcntl(0, F_GETFL);


    //设置
    return fcntl(0, F_SETFL, (O_ASYNC | flags));
}


void input_handler();
void  setup_aio_buffer();
struct aiocb  aio_struct;

int main(){



    signal(SIGIO, input_handler);
    /**
     * 初始化设置
     */
    setup_aio_buffer();
    aio_read(&aio_struct);
}

void setup_aio_buffer(){

    static char input[1];

    aio_struct.aio_fildes = 0;    //标准输入
    aio_struct.aio_buf    = input; //输入Buffer
    aio_struct.aio_nbytes = 1;     //每次读取的字节数
    aio_struct.aio_offset = 0;     //下标

    /**
     * 要触发啥信号
     */
    aio_struct.aio_sigevent.sigev_notify = SIGEV_SIGNAL; //通知类型，有三种:SIGEV_NONE  没有异步通知。SIGEV_SIGNAL:完成时通知。SIGEV_THREAD：call notification function
    aio_struct.aio_sigevent.sigev_signo = SIGIO;


}

/**
 * 接收数据
 */
void input_handler(){
    char * cp = (char *) aio_struct.aio_buf;

    if(aio_error(&aio_struct) != 0){

        perror("aio读取错误");
    }


    if(aio_return(&aio_struct) == 1){

        printf("%c", *cp);
    }

    aio_read(&aio_struct);
}


