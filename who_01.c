//
// Created by Wen on 2018/2/5.
//      last who  学习:  使用man who 服务帮助文件  ，会显示其实登录会话保存在/var/run/utmpx这个文件中的
//  可以使用/usr/include/utmptx.h 里面的东西将其会话信息读取出来~~~ （os-x 10.8）之前数据保存
//在/var/admn/utmpt 中，使用utmp.h读取数据

//


#include <stdio.h>
#include <utmpx.h>
#include <fcntl.h>
#include <unistd.h>

#include <utmp.h>
void show_info(struct utmpx * record);


int  main(){

    struct utmpx current_record;
    int utmp_fd;
    int read_len = sizeof(current_record);

    if ((utmp_fd = open(UTMPX_FILE, O_RDONLY)) == -1) {

        perror(UTMPX_FILE);
        exit(1);
    }

    while (  read(utmp_fd, &current_record, read_len) ==  read_len) {
        show_info(&current_record);
    }


    close(UTMPX_FILE);

    return 0;
}



void show_info(struct utmpx * record){

    printf("%-8.8s \n ", record->ut_id);
//    printf("%-8.8s ", record->ut_line);
//   // printf("%-8.8s ", record->ut_type);
//    printf("%-8.8s ", record->ut_host);

}
