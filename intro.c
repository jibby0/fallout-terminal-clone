// 
// File: intro.c 
// intro.c plays the introduction sequence
// @author Josh Bicking <josh1147582>
// // // // // // // // // // // // // // // // // // // // // // // 

#define _BSD_SOURCE /* for unistd.h */
#ifdef _WIN32
// Windows implements sleep in Windows.h with Sleep(milliseconds)
#   include <curses.h>
#   include <Windows.h>
#   define SLEEP(delay) Sleep(delay/1000)
#else
// Unix requires unistd.h for usleep(microseconds).
// usleep/1000 = Sleep
#   include <ncurses.h>
#   include <unistd.h>
#   define SLEEP(delay) usleep(delay)
#endif

#include <string.h>

#include "print.h"
#include "intro.h"


/// Plays the introduction sequence. 
///
void intro(){
    clear();
    SLEEP(250000);
    
    // Get the size of the terminal window. 
    // The size of the game window is 53x22.
    int BUFF_Y = 0, BUFF_X = 0;
    int y, x;
    getmaxyx(stdscr, y, x);

    if(y > 22)
        BUFF_Y = y/2 - 22/2;
    if(x > 53)
        BUFF_X = x/2 - 53/2;

    slowPrint("WELCOME TO ROBCO INDUSTRIES (TM) TERMLINK", 0, BUFF_Y, BUFF_X);

    move(1, 0);
    refresh();
    SLEEP(30000);
    mvprintw(2,0,"%c", '>');
    move(2,1);
    refresh();
    SLEEP(1500000);

    slowType("SET TERMINAL/INQUIRE", 2, BUFF_Y, BUFF_X);

    slowPrint("RIT-V300", 4, BUFF_Y, BUFF_X);

    mvprintw(6,0,"%c", '>');
    refresh();
    SLEEP(1500000);
    slowType("SET FILE/PROTECTION=OWNER:RWED ACCOUNTS.F",6, BUFF_Y, BUFF_X);
    
    mvprintw(7,0,"%c", '>');
    refresh();
    SLEEP(1500000);
    slowType("SET HALT RESTART/MAINT",7, BUFF_Y, BUFF_X);
    
    slowPrint("Initializing Robco Industries(TM) Boot Agent v2.3.0",9, BUFF_Y, BUFF_X);

    slowPrint("RBIOS-4.02.08.00 53EE5.E7.E8",10, BUFF_Y, BUFF_X);

    slowPrint("Copyright 2201-22-3 Robco Ind.",11, BUFF_Y, BUFF_X);

    slowPrint( "Uppermem: 64 KB",12, BUFF_Y, BUFF_X);

    slowPrint("Root (5A8)",13, BUFF_Y, BUFF_X);

    slowPrint("Maintenance Mode",14, BUFF_Y, BUFF_X);

    mvprintw(16,0,"%c",'>');
    refresh();
    SLEEP(1500000);
    slowType("RUN DEBUG/ACCOUNTS.F",16, BUFF_Y, BUFF_X);
    move(16,0);
    refresh();
    SLEEP(50000);
}

