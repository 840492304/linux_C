//
// Created by Wen on 2018/2/23.
//


/**
 * pwd命令的实现
 */
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <zconf.h>
#include <string.h>

ino_t get_path_node(char * file_name);
char * inode_to_filenam(ino_t  inode);

int main(){



    /**
     * 如果当前i-节点号与 父目录的i-node相同，说明已经是根目录了
     */
    while(get_path_node("..") != get_path_node(".")){

        ino_t ino;
        ino = get_path_node(".");
        //获取当前的路径名
        inode_to_filenam(ino);
        /**
           * 切换到上一个
           */
        chdir("..");


    }

}


/**
 * 根据文件名获取I节点号
 * @param file_name
 * @return
 */

ino_t get_path_node(char * file_name){

    struct stat info;

    if (stat(file_name, &info) == -1) {

        perror("path error");
    }

    return info.st_ino;
}


/**
 * I节点转换成文件名  ->
 * @param inode
 * @return
 */
char * inode_to_filenam(ino_t  inode){

        //readdir()
    DIR * dir_ptr;

    struct dirent * dirent_ptr;



    dir_ptr = opendir("..");

    if (opendir == NULL) {

        perror("dir error");
    }

    while(( dirent_ptr = readdir(dir_ptr)) != NULL){

        if (dirent_ptr->d_ino == inode) {

            printf("/%s", dirent_ptr->d_name);
        }

    }




}