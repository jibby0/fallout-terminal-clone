#ifdef _WIN32
// Windows builds require curses.h for the PDcurses library.
#   include <curses.h>
#else
// Unix builds require ncurses.h for the Ncurses library.
#   include <ncurses.h>
#endif

#include <stdlib.h>
#include <time.h> /* For making a random seed */
#include <string.h> /* For strcmp, to identify argv[1] */
#include "intro.h" /* To launch intro */
#include "pass.h" /* To launch pass */
#include "wordParse.h" /* To read the file */

int main(int argc, char * argv[]){

    if(argc > 1 && !strcmp(argv[1], "--help")){
        printf("Usage: %s [--DIFFICULTY]\n\n[--DIFFICULTY] is an optional argument"
                " that uses built in words instead\nof words specifed in the config"
                " file. Options are:\n\n"
                "--veryEasy,\t10 words, 5 letters per word (default)\n\n"
                "--easy,\t\t11 words, 7 letters per word\n\n"
                "--average,\t14 words, 9 letters per word\n\n"
                "--hard,\t\t7 words, 11 letters per word\n\n"
                "--veryHard,\t13 words, 12 letters per word\n\n"
                "If no difficulty is provided, this program will read input "
                "from the FalloutTerminal.cfg file. If this file cannot be found "
                "or the configuration is invalid, it will default to Very Easy." 
                , argv[0]);
        exit(0);
    }

    // Check if a difficulty arg was given
    if(argc > 1){
        if(!strcmp(argv[1], "--veryEasy")) {
            setVeryEasy();
        }
        if(!strcmp(argv[1], "--easy")) {
           setEasy();
        } 
        else if(!strcmp(argv[1], "--average")) {
           setAverage();
        } 
        else if(!strcmp(argv[1], "--hard")) {
           setHard();
        } 
        else if(!strcmp(argv[1], "--veryHard")) {
           setVeryHard();
        } 
        else {
            printf("Invalid command. Type \"%s --help\" for usage and a list of commands.\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    // Otherwise, read the file for words
    else {    
        readWordsFromFile();
    }

    // Read what should be launch on completion/victory
    readLaunches();

    // Read the key config
    readKeys();

    // Gen a random seed
    srand ( (unsigned)time(NULL) );

    // Begin curses
    initscr();
    noecho();
    refresh();
    attron(A_BOLD);
    nodelay(stdscr, 1);
    keypad(stdscr, TRUE);
    // Check for color support. Start color if it exists.
    if(has_colors() == 1){
        start_color();
        init_pair(1,COLOR_GREEN,COLOR_BLACK);
        attron(COLOR_PAIR(1));
    }

    // Run intro
    intro();

    // Run pass
    pass();

    return EXIT_SUCCESS;
}

