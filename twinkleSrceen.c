//
// Created by Wen on 2018/2/28.
//亮瞎狗眼  结果并没有亮瞎狗眼，只是 将字颜色反转了
//

#include <curses.h>
#include <zconf.h>
#include <tclDecls.h>

void sleep_ms(unsigned int secs);

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
        refresh();
        Tcl_Sleep(100);
       // sleep_ms(10);
        move(i, i * 2);

        addstr("             ");


    }

    getch();
    endwin();

}


void sleep_ms(unsigned int secs)

{

    struct timeval tval;

    tval.tv_sec=secs/1000;

    tval.tv_usec=secs%1000;

    select(0,NULL,NULL,NULL,&tval);

}