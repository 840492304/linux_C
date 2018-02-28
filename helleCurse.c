//
// Created by Wen on 2018/2/28.
//

#include <curses.h>
#include <stdio.h>


int main(){

    /**
     * 初始化屏幕
     */
    initscr();

    /**
     * 清除屏幕
     */
    clear();


    move(20, 60);

//    addstr("hello 调库仔");
    addstr("hello heihei");

    move(LINES-1, 0);

    refresh();

    getch();

    endwin();

    return 1;

}