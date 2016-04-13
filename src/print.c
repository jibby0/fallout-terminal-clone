// 
// File: print.c 
// print.c handles printing of pre-game strings
// @author Josh Bicking <josh1147582>
// // // // // // // // // // // // // // // // // // // // // // // 

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

#include <stdlib.h>
#include <time.h>
#include "print.h"
#include "FalloutTerminal.h"

void slowPrint(char arr[], int size, int line){
    for(int i=0; i<size; i++){  
        /* Print the current character in the current position. */
        mvprintw(line,i,"%c",arr[i]);
        /* Move the cursor to the next position */
        move(line, i+1);
        refresh();
        /* If any keyboard input was recieved, go directly to pass(), otherwise continue */
        if(kbhit()){
            pass();
        }
        SLEEP(20000);
    }
    return;
}

void slowType(char arr[], int size, int line){
    for(int i=0; i<size; i++){  
        mvprintw(line,i+1,"%c",arr[i]);
        move(line, i+2);
        refresh();
        if(kbhit()){
            pass();
        }
        SLEEP(70000);
    }
    return;
}

void passPrint(char arr[], int size, int line){
    int i;
    for(i=0; i<size; i++){  
        mvprintw(line,i,"%c",arr[i]);
        move(line, i+1);
        refresh();
        SLEEP(20000);
    }
}

int kbhit(){
    /* Get the current char. */
    int ch = getch();

    /* Returns true if a key has been hit. False if it hasn't. */ 
    if (ch != ERR) {
        return 1;
    } else {
        return 0;
    }
}

void printChoices(int hex, char arr[], int line, int offset){
    mvprintw(line,offset,"0x%X", hex);
    for(int i=0; i<12; i++)
        mvprintw(line,7+offset+i,"%c",arr[i]);
    move(line, 20+offset);
    refresh();
    SLEEP(30000);
}

// end
