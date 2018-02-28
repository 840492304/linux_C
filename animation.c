//
// Created by Wen on 2018/2/28.
//


#include <curses.h>
#include <zconf.h>

#define LEFTEDGE 1
#define RIGTHEDGE 15
#define STEP 1
#define CLEARCHAR "              "
#define MESSAGE "233333"
#define HIGH 20

int main(){

    initscr();

    int pos = LEFTEDGE;
    int step = STEP;

    while (1) {

        pos = pos + step;

        move(pos, HIGH);
        addstr(MESSAGE);
        refresh();
        sleep(1);
        move(pos, HIGH);
        addstr(CLEARCHAR);

        clear();

        if (pos >= RIGTHEDGE) {
            step = -STEP;
        }

        if (pos <= LEFTEDGE) {
            step = STEP;
        }

    }

}