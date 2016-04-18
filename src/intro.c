#define _BSD_SOURCE /* for unistd.h */

#ifdef _WIN32
#   include <Windows.h>
#   include <curses.h>
#   define SLEEP(delay) Sleep(delay/1000)
// Unix builds require ncurses.h for the Ncurses library.
// Unix also requires unistd.h for usleep(microseconds).
// usleep/1000 = Sleep
#else
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
    
    slowPrint("WELCOME TO ROBCO INDUSTRIES (TM) TERMLINK",strlen("WELCOME TO ROBCO INDUSTRIES (TM) TERMLINK"), 0);

    move(1, 0);
    refresh();
    SLEEP(30000);
    mvprintw(2,0,"%c", '>');
    move(2,1);
    refresh();
    SLEEP(1500000);

    slowType("SET TERMINAL/INQUIRE",strlen("SET TERMINAL/INQUIRE"), 2);

    slowPrint("RIT-V300",strlen("RIT-V300"), 4);

    mvprintw(6,0,"%c", '>');
    refresh();
    SLEEP(1500000);
    slowType("SET FILE/PROTECTION=OWNER:RWED ACCOUNTS.F",strlen("SET FILE/PROTECTION=OWNER:RWED ACCOUNTS.F"),6);
    
    mvprintw(7,0,"%c", '>');
    refresh();
    SLEEP(1500000);
    slowType("SET HALT RESTART/MAINT",strlen("SET HALT RESTART/MAINT"),7);
    
    slowPrint("Initializing Robco Industries(TM) Boot Agent v2.3.0",strlen("Initializing Robco Industries(TM) Boot Agent v2.3.0"),9);

    slowPrint("RBIOS-4.02.08.00 53EE5.E7.E8",strlen("RBIOS-4.02.08.00 53EE5.E7.E8"),10);

    slowPrint("Copyright 2201-22-3 Robco Ind.",strlen("Copyright 2201-22-3 Robco Ind."),11);

    slowPrint( "Uppermem: 64 KB",strlen("Uppermem: 64 KB"),12);

    slowPrint("Root (5A8)",strlen("Root (5A8)"),13);

    slowPrint("Maintenance Mode",strlen("Maintenance Mode"),14);

    mvprintw(16,0,"%c",'>');
    refresh();
    SLEEP(1500000);
    slowType("RUN DEBUG/ACCOUNTS.F",strlen("RUN DEBUG/ACCOUNTS.F"),16);
    move(16,0);
    refresh();
    SLEEP(50000);
}

