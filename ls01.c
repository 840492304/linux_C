//
// Created by Wen on 2018/2/18.
//

/**
 *
 * 文件夹其实也是一个文件，通过openDir去打开文件夹获取一个Dir的指针，然后通过循环readDir,遍历获取到文件信息，
 * 文件夹信息保存到一个dirent结构体里面
 *
 *
 *
 */

#include <stdio.h>
#include <dirent.h>

void my_ls(char []);

void main(int ac, char * av[]){


    char * dirName;

    printf("%d  ", ac);

    /**
     * 默认打开当前文件夹
     */
    if (ac == 1) {

        dirName = ".";

        my_ls(dirName);
    }else{

        while (--ac){

            printf("当前打开文件夹是:%s", *++av);

            dirName = *av;

            my_ls(dirName);
        }
    }
}

void my_ls(char dirName[]){

    DIR *dirPtr;
    struct dirent * _dirent_ptr;
    dirPtr = opendir(dirName);

    if (dirPtr ==  NULL) {

        perror("无法打开文件夹");
        return;
    }

    while((_dirent_ptr = readdir(dirPtr)) != NULL){

        printf("%s   \n", _dirent_ptr->d_name);
    }


}