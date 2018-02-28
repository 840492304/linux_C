//
// Created by Wen on 2018/2/28.
//亮瞎狗眼  结果并没有亮瞎狗眼，只是 将字颜色反转了
//

#include <curses.h>


int main(){

    initscr();


    for (int i = 0; i < LINES; ++i) {

        move(i, i * 2);

        if (i % 2 == 1) {

            standout();
        }

        addstr("233333");
        if (i % 2 == 1) {
            standend();
        }

    }
    refresh();

    getch();
    endwin();

}