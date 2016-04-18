#ifdef _WIN32
#   include <curses.h>
#else
#   include <ncurses.h>
#endif

#include <stdlib.h>
#include <time.h>
#include "intro.h"
#include "pass.h"

int main(){

    // TODO  get input from args here. Pass it to pass

    srand ( (unsigned)time(NULL) );
    initscr();
    noecho();
    refresh();
    attron(A_BOLD);
    nodelay(stdscr, 1);
    if(has_colors() == 1){
        /* Colors */
        start_color();
        init_pair(1,COLOR_GREEN,COLOR_BLACK);
        attron(COLOR_PAIR(1));
    }

    intro();
    pass();
    
    return 0;
}
