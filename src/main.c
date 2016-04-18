#ifdef _WIN32
#   include <curses.h>
#else
#   include <ncurses.h>
#endif

#include <stdlib.h>
#include <time.h>
#include "intro.h"
#include "pass.h"
#include "fileParse.h"

int main(int argc, char * argv[]){

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

    FILE *fp = NULL;

    if(argc > 1)
        fp = fopen(argv[1], "r");

    readFile(fp);

    intro();
    pass();

    
    return 0;
}

