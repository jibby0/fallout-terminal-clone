// 
// File: pass.c 
// pass.c plays the password guessing game
// @author Josh Bicking <josh1147582>
// // // // // // // // // // // // // // // // // // // // // // // 

#define _BSD_SOURCE // for unistd.h
#ifdef _WIN32
#   include <Windows.h>
#   include <curses.h>
#   define SLEEP(delay) Sleep(delay/1000)
#else
#   include <ncurses.h>
#   include <unistd.h>
#   define SLEEP(delay) usleep(delay)
#endif

#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "pass.h"
#include "print.h"
#include "wordParse.h"
#include "intro.h"

#define OFFSET_LEFT 0
#define OFFSET_RIGHT 20
#define BIGSTRING_SIZE 408

static int currentCharContains(char arr[],char c){
    int i;
    for(i=0; i<12; i++)
        if(arr[i]==c)
            return 1;
    return 0;
}

static int getCharLoc(int y, int x){
    // Left side
    if(x<19)
        return 12*(y-5)+(x-7);
    // Right side
    else
        return 12*(y-5)+(x-27+204);
}

void pass(){
    
    // Clear the screen
    erase();

    // Intro text
    passPrint("ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL",0);
    
    passPrint("ENTER PASSWORD NOW", 1);

    passPrint("4 ATTEMPT(S) LEFT: * * * *", 3);
    
    // Generate the hex values on the left sides
    int arbHex;
    arbHex = (rand() % 200) + 63744;
    
    // Generate the string to hold the bracket tricks and words
    char bigString [BIGSTRING_SIZE];
    char randValues[] = "!@#$%^*()_-=+\\|/[]{}?\"\':;,.<>";
    int i;
    for(i=0; i<BIGSTRING_SIZE; i++){
        // Fill bigString with random values
        bigString[i] = randValues[rand()%29];
    }

    char ** wordArr = getWordArr();
    
    int WORD_POOL_SIZE = getNumWords(); 
    int WORD_SIZE = getWordLength();
    int WORDS_CHOSEN = getWordsToChoose(); 
    

    // Place a word in the string total times, making sure it doesn
    // overwrite another word or get placed right next to it 
    int place;                      // Current place for checking and word insertion
    int takenWords[WORDS_CHOSEN];   // Words already placed in bigString

    for(int i=0; i<WORDS_CHOSEN; i++)
        takenWords[i] = 0;

    int valid;                      // 1 if selected word is not already used a
                                    // does not conflict with other words, 0 otherwise */
    int pickedWord = 0;             // Indicate whether or not we've chosen the correct word
    int left = WORDS_CHOSEN;        // # of words that still need to be chosen
    char correctWord[WORD_SIZE];    // the correct word
    while(left>0){  
        valid = 1;
        
        // Choose a random place in bigString
        place = rand()%(BIGSTRING_SIZE-WORD_SIZE);
        
        // Check of any characters there or around it are A-Z
        for(i=place-1; i<place+WORD_SIZE+1; i++){
            if(bigString[i] > 64 && bigString[i] < 91){
                valid = 0;
                break;
            }
        }


        if(valid){
            int wordLoc = rand()%WORD_POOL_SIZE;

            if(takenWords[wordLoc])
                valid=0;

            if(valid){

                takenWords[wordLoc] = 1;

                // Add the word to bigString
                for(i=place; i<place+WORD_SIZE; i++){
                    bigString[i] = *(*(wordArr+wordLoc)+(i-place));
                    // If this is the first word chosen, it is the correct word.
                    if(!pickedWord)
                        correctWord[i-place] = *(*(wordArr+wordLoc)+(i-place));
                }
                pickedWord = 1;
                left--;
            }
        }
    }
    
    
    // Create and fill an array to keep track of which brackets were used
    int usedBrackets[BIGSTRING_SIZE];
    for(i=0; i<BIGSTRING_SIZE; i++){
        usedBrackets[i] = 1;
    }
    
    
    // Print the hex and the filled bigString
    char temp[12];  
    int current = 0;
    for(i=5; i<22; i++){
        // Print left side
        for(int j=0; j<12; j++){
            temp[j] = bigString[j+current];
        }
        printChoices(arbHex,temp,i, OFFSET_LEFT);
        current = current + 12;
        arbHex = arbHex + 12;
    }
    
    for(i=5; i<22; i++){
        // Print right side
        for(int j=0; j<12; j++){
            temp[j] = bigString[j+current];
        }
        printChoices(arbHex,temp,i, OFFSET_RIGHT);
        current = current + 12;
        arbHex = arbHex + 12;
    }
    
    
    mvprintw(21,40,"%c",'>');
    move(5,7);
    char currentChar[12]; // Max length currentChar could be (total possible length of a bracket trick)
    currentChar[0] = (char)mvinch(5,7);

    int y,x,origy,origx,starty,startx;  // values that keep track of current yx locations, and original ones
    int wordLength;                     // How long a word is
    int charStart;                      // where character counting starts for brackets
    int keyPress;                      // key pressed by user
    int charCounter;                    // counts currentChar - used for incrementing currentChar to print or change it
    int bracketLength;                  // length of a bracket trick
    char endBracket;                    // the end bracket that corresponds to currentChar[0];
    int bracketTricks=0;                // Total number of bracket tricks used
    int needsClearing = 0;              // Whether or not highlights need to be pur
    int needsClearingMultiLine = 0;     // Whether or not a multi line highlight needs to be purged
    char output[13];                    // Used for side terminal output
    int allowances = 4;
    

    // Get the key config
    int GO_LEFT, GO_RIGHT, GO_DOWN, GO_UP;
    switch(getKeyConfig()){
        case ARROWS: 
            GO_LEFT = KEY_LEFT;
            GO_RIGHT = KEY_RIGHT;
            GO_UP = KEY_UP;
            GO_DOWN = KEY_DOWN;
            break;
        case WASD: 
            GO_LEFT = 'a';
            GO_RIGHT = 'd';
            GO_UP = 'w';
            GO_DOWN = 's';
            break;
        case HJKL: 
            GO_LEFT = 'h';
            GO_RIGHT = 'l';
            GO_UP = 'k';
            GO_DOWN = 'j';
            break;
    }

    // Get rid of all typed characters
    int ch = getch();
    while(ch != ERR)
        ch = getch();
    // Finally, set nodelay to false so we can wait for input
    nodelay(stdscr, 0);

    while(1){
        getyx(stdscr,y,x);
        
        // Get allowances left
        mvprintw(1,0,"                                 ");
        mvprintw(3,0,"                              ");
        switch(allowances){
            case 1: mvprintw(3,0,"1 ATTEMPT(S) LEFT: *");
                    attron(A_BLINK);
                    mvprintw(1,0,"!!! WARNING: LOCKOUT IMNINENT !!!");
                    attroff(A_BLINK);
                    attron(A_BOLD);
                    break;
            case 2: mvprintw(3,0,"2 ATTEMPT(S) LEFT: * *");
                    mvprintw(1,0,"ENTER PASSWORD NOW");
                    break;
            case 3: mvprintw(3,0,"3 ATTEMPT(S) LEFT: * * *");
                    mvprintw(1,0,"ENTER PASSWORD NOW");
                    break;
            case 4: mvprintw(3,0,"4 ATTEMPT(S) LEFT: * * * *");
                    mvprintw(1,0,"ENTER PASSWORD NOW");
                    break;
            case 0: clear();
                    mvprintw(10,20,"TERMINAL LOCKED");
                    mvprintw(12,12,"PLEASE CONTACT AN ADMINISTRATOR");
                    refresh();
                    SLEEP(3000000);
                    endwin();
                    if(strlen(getCompleteProg())> 2)
                        system(getCompleteProg());
                    freeAll();
                    exit(EXIT_FAILURE);
        }
        refresh();
        move(y,x);
        // Check if highlights need to be purged
        if(needsClearing){
            charCounter = 0;
            while(charCounter!=bracketLength+1){
                currentChar[charCounter] = (char)mvinch(origy,charStart+charCounter);
                mvprintw(origy,charStart+charCounter,"%c",(int)currentChar[charCounter]);
                charCounter++;
            }
            mvprintw(21,41,"            ",currentChar[0]);
            needsClearing = 0;
            move(y,origx);
        }
        if(needsClearingMultiLine){
            charCounter = 0;
            while(charCounter!=wordLength){
                currentChar[charCounter] = (char)mvinch(starty,startx);
                mvprintw(starty,startx,"%c",currentChar[charCounter]);
                charCounter++;
                startx++;
                if(startx==19 || startx==39){
                    startx-=12;
                    starty++;
                    if(starty == 22) {
                        starty = 5;
                        startx+=20;
                    }
                }
            }
            mvprintw(21,41,"            ",currentChar[0]);
            needsClearingMultiLine = 0;
            move(y,x);
        }
        // Clear the char array
        for(i=0;i<12;i++)
            currentChar[i]=' ';
        currentChar[0] = (char) (char)mvinch(y,x);
        // Set the new y and x to origy and origx
        origy = y;
        origx = x;
        // Check for bracket tricks
        if((currentChar[0]=='(' || currentChar[0]=='<' || currentChar[0]=='[' || currentChar[0]=='{') && usedBrackets[getCharLoc(y,x)] && bracketTricks<WORDS_CHOSEN){
            charStart = x;
            bracketLength=0;
            while(x!=18 && x!=38){
                x++;
                endBracket = (char)mvinch(y,x);
                bracketLength++;
            if((endBracket == ')' && currentChar[0]=='(') || 
                (endBracket == '>' && currentChar[0]=='<') || 
                (endBracket == ']' && currentChar[0]=='[') || 
                (endBracket == '}' && currentChar[0]=='{')){
                    // Reprint the bracket trick with highlight
                    attron(A_STANDOUT);
                    charCounter = 0;
                    while(1){
                        currentChar[charCounter] = (char)mvinch(y,charStart+charCounter);
                        mvprintw(y,charStart+charCounter,"%c",currentChar[charCounter]);
                        if(currentChar[charCounter] == endBracket)
                            break;
                        charCounter++;
                    }
                    attroff(A_STANDOUT);
                    // Print the bracket trick to output
                    attron(A_BOLD);
                    for(i=0;i<=charCounter;i++)
                        mvprintw(21,41+i,"%c",(int)currentChar[i]);
                    // Notify that highlighting will need to be cleared next move
                    needsClearing = 1;
                }
            }
            if(!((endBracket == ')' && currentChar[0]=='(') || 
                (endBracket == '>' && currentChar[0]=='<') || 
                (endBracket == ']' && currentChar[0]=='[') || 
                (endBracket == '}' && currentChar[0]=='{'))){
                mvprintw(21,41,"%c",currentChar[0]);
            }
        }
        // Check for letters
        else if(currentChar[0]>64 && currentChar[0]<91){
            // Check for letter behind the current location
            int tempx = x;
            int tempy = y;
            while(bigString[getCharLoc(tempy,tempx)-1]>64 && bigString[getCharLoc(tempy,tempx)-1]<91){
                currentChar[0] = bigString[getCharLoc(tempy,tempx)];
                tempx--;
                if(tempx==6 || tempx==26){
                    tempx+=12;
                    tempy--;
                    if(tempy == 4){
                        tempy = 21;
                        tempx-=20;
                    }
                }
            }
            startx = tempx;
            starty = tempy; // We'll need the location of the first char for clean
            // And start there
            charCounter = 0;
            while(bigString[getCharLoc(tempy,tempx)+1]>64 && bigString[getCharLoc(tempy,tempx)+1]<91){
                currentChar[charCounter] = bigString[getCharLoc(tempy,tempx)];
                charCounter++;
                tempx++;
                if(tempx==19 || tempx==39){
                    tempx-=12;
                    tempy++;
                    if(tempy == 22) {
                        tempy = 5;
                        tempx+=20;
                    }
                }
            }
            // Now currentChar is the String, and charCounter+1 is the length
            wordLength = charCounter+1;
            // Reprint the word with highlight
            tempx = startx;
            tempy = starty;
            attron(A_STANDOUT);
            charCounter = 0;
            while(charCounter!=wordLength){
                currentChar[charCounter] = (char)mvinch(tempy,tempx);
                mvprintw(tempy,tempx,"%c",currentChar[charCounter]);
                charCounter++;
                tempx++;
                if(tempx==19 || tempx==39){
                    tempx-=12;
                    tempy++;
                    if(tempy == 22) {
                        tempy = 5;
                        tempx+=20;
                    }
                }
            }
                    attroff(A_STANDOUT);
                    // Print the word to output
                    attron(A_BOLD);
                    for(i=0;i<charCounter;i++)
                        mvprintw(21,41+i,"%c",(int)currentChar[i]);
                    // Notify that highlighting will need to be cleared next move
                    needsClearingMultiLine = 1;
        }
        // Nothing was found, print current char
        else
            mvprintw(21,41,"%c",currentChar[0]);
        
        move(origy,origx);
        refresh();
        
        keyPress = getch();
        getyx(stdscr,y,x);
        if(keyPress==GO_UP){
            if(y>5)
                move(y-1,x);
        }
        if(keyPress==GO_DOWN){
            if(y<21)
                move(y+1,x);
        }
        if(keyPress==GO_LEFT){
            if(x>7){
                if(x==27)
                    move(y,18);
                else
                    move(y,x-1);
            }
                
        }
        if(keyPress==GO_RIGHT){
            if(x<38){
                if(x==18)
                    move(y,27);
                else
                    move(y,x+1);
            }
        }
        if(keyPress==3)     // Ctrl-C
            exit(0);
        if(keyPress=='\n'){ // Enter
            // Get past answers and shift them up along the right.
            // This "log" handles 5 preivous commands.

            mvprintw(5,41,"              ");
            mvprintw(6,41,"              ");
            mvprintw(7,41,"              ");

            char buf[15];
            for(int i=8; i<19; i+=3) {
                for(int j=0; j< 3; j++){
                    mvinnstr(i+j, 40, buf, 14);
                    mvprintw(i+j,40,"              ");
                    mvprintw(i+j-3, 40, "%s", buf);
                }
            }
            // If the char is a left bracket
            if(((currentChar[0]=='(') && currentCharContains(currentChar,')')) || 
               (currentChar[0]=='<' && currentCharContains(currentChar,'>')) || 
               (currentChar[0]=='[' && currentCharContains(currentChar,']')) || 
               (currentChar[0]=='{' && currentCharContains(currentChar,'}'))){
                // Set the selected bracket as used
                usedBrackets[getCharLoc(y,x)] = 0;
                // Increment total bracket tricks used
                bracketTricks++;
                if(rand()%5==0){
                    // 20% chance of allowance replenish
                    mvinnstr(21,40, buf, 14);
                    mvprintw(17,40, "%s", buf);
                    sprintf(output,"Allowance   ");
                    mvprintw(18,40,">");
                    for(i=0;i<12;i++){
                        mvprintw(18,41+i,"%c",output[i]);
                    }
                    sprintf(output,"replenished.");
                    mvprintw(19,40,">");
                    for(i=0;i<12;i++){
                        mvprintw(19,41+i,"%c",output[i]);
                    }
                    allowances = 4;
                }
                else{
                    // Remove a dud
                    int tempx,tempy;
                    pickagain:do{
                        if(rand()%2==0)
                        tempx = (rand()%12)+7;
                    else
                        tempx = (rand()%12)+27;
                    tempy = (rand()%17)+5;
                    } while(!(bigString[getCharLoc(tempy,tempx)]>64 && bigString[getCharLoc(tempy,tempx)]<91));
                    while(bigString[getCharLoc(tempy,tempx)-1]>64 && bigString[getCharLoc(tempy,tempx)-1]<91){
                        tempx--;
                        if(tempx==6 || tempx==26){
                            tempx+=12;
                            tempy--;
                        }
                    }

                    startx = tempx;
                    starty = tempy;
                    
                    charCounter = 0;
                    while(bigString[getCharLoc(tempy,tempx)+1]>64 && bigString[getCharLoc(tempy,tempx)+1]<91){
                        currentChar[charCounter] = bigString[getCharLoc(tempy,tempx)];
                        charCounter++;
                        tempx++;
                        if(tempx==19 || tempx==39){
                            tempx-=12;
                            tempy++;
                        }
                    }
                    // Check if currentChar = correctWord
                    int allCorrect=1;
                    for(i=0;i<WORD_SIZE;i++){
                        if(currentChar[i]!=correctWord[i])
                            allCorrect = 0;
                    }
                    if(allCorrect)
                        goto pickagain;
                    
                    tempx = startx;
                    tempy = starty;
                    while(bigString[getCharLoc(tempy,tempx)]>64 && bigString[getCharLoc(tempy,tempx)]<91){
                        mvprintw(tempy,tempx,"%c",'.');
                        bigString[getCharLoc(tempy,tempx)] = '.';
                        tempx++;
                        if(tempx==19 || tempx==39){
                            tempx-=12;
                            tempy++;
                        }
                    }
                    
                    mvinnstr(21,40, buf, 14);
                    mvprintw(17,40, "%s", buf);
                    mvprintw(18,40,">Dud");
                    mvprintw(19,40,">removed.");
            
                }
            }
            // Else compare it to the correct word
            else{
                int rightLetters = WORD_SIZE;
                for(i=0;i<WORD_SIZE; i++){
                    if(currentChar[i]!=correctWord[i])
                        rightLetters--;
                }
                if(rightLetters==WORD_SIZE){
                    mvprintw(15,40,">");
                    for(i=0;i<12;i++){
                        mvprintw(15,41+i,"%c",currentChar[i]);
                    }
                    sprintf(output,"Exact match!");
                    mvprintw(16,40,">");
                    for(i=0;i<12;i++){
                        mvprintw(16,41+i,"%c",output[i]);
                    }
                    sprintf(output,"Please wait ");
                    mvprintw(17,40,">");
                    for(i=0;i<12;i++){
                        mvprintw(17,41+i,"%c",output[i]);
                    }
                    sprintf(output,"while system");
                    mvprintw(18,40,">");
                    for(i=0;i<12;i++){
                        mvprintw(18,41+i,"%c",output[i]);
                    }
                    sprintf(output,"is accessed.");
                    mvprintw(19,40,">");
                    for(i=0;i<12;i++){
                        mvprintw(19,41+i,"%c",output[i]);
                    }
                    refresh();
                    SLEEP(3000000);
                    endwin();
                    if(strlen(getVictoryProg()) > 2)
                        system(getVictoryProg());
                    else if(strlen(getCompleteProg())> 2)
                        system(getCompleteProg());
 
                    freeAll();
                    exit(EXIT_SUCCESS);
                    
                }
                else{
                    mvprintw(17,40,">");
                    for(i=0;i<12;i++){
                        mvprintw(17,41+i,"%c",currentChar[i]);
                    }
                    sprintf(output,"Entry denied");
                    mvprintw(18,40,">");
                    for(i=0;i<12;i++){
                        mvprintw(18,41+i,"%c",output[i]);
                    }
                    sprintf(output,"%d/%d correct.",rightLetters,WORD_SIZE);
                    mvprintw(19,40,">");
                    for(i=0;i<12;i++){
                        mvprintw(19,41+i,"%c",output[i]);
                    }
                    allowances--;
                }
            }
            move(y,x);
        }   
        refresh();
        
    }

    endwin();
    freeAll();
    exit(EXIT_SUCCESS);
}
