// 
// File: wordParse.c 
// wordParse.c builds a table of words for pass() to use. It either uses
// predefined words, or words read in from the config file.
// @author Joshua Bicking <josh1147582>
// // // // // // // // // // // // // // // // // // // // // // // 

#include "getline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordParse.h"
#include <ctype.h>

#define MAX_WORD_SIZE 12

char **wordArr;

int numWords;

int wordsToChoose;

char * victoryProg;
char * completeProg;

void readWordsFromFile(FILE* fp){

    if(fp == NULL) {
        setVeryEasy();
        return;
    }

    // Check if FalloutTerminal.cfg is invalid
    char * buf;
    size_t n = 0;
    
    numWords = 0;

    while(getline(&buf, &n, fp)){
        if(buf[0] == '#' || !strcmp(buf, "\n")) 
            continue;

        // Remove the \n at the end of buff
        buf[strlen(buf)-1] = '\0';

        // Stop on :LAUNCH_ON_*
        if(buf[0] == ':' ) {
            if(!strncmp(buf, ":WORDS_TO_CHOOSE=",17)) {
                sscanf(buf+17, "%d", &wordsToChoose);
                continue;
            }
            else
                break;
        }

        // Check all chars in buf are A-Z or a-z
        int invalidChars = 0;
        for(int i=0; (unsigned long)i<strlen(buf); i++){
           if(buf[i] > 64 && buf[i] < 91)
              continue;
           else if(buf[i] > 96 && buf[i] < 123)
               buf[i] = toupper(buf[i]);
           else
               invalidChars = 1;
        }

        if(invalidChars)
            continue;


        // Check all words are the same size as the first word
        if(numWords != 0) {
            if(strlen(buf) != strlen(*wordArr))
                continue;

            // Check the word doesn't already exist in the list
            int dupes = 0;
            for(int i=0; i < numWords; i++)
                if(!strcmp(*(wordArr+i), buf))
                    dupes = 1;

            if(dupes)
                continue;
        }


        // Read the word into wordArr

        wordArr = realloc(wordArr, sizeof(char*) * numWords+1);

        *(wordArr+numWords) = malloc(sizeof(char) * sizeof(buf));
        strncpy(*(wordArr+numWords),buf, MAX_WORD_SIZE);

        numWords++;
    }

    if(wordsToChoose == 0)
        wordsToChoose = 7; 

    if(wordsToChoose > numWords){
        // Too few valid words recieved: default to very easy
        free(wordArr);
        setVeryEasy();
    }

    free(buf);
}

void readLaunches(FILE* fp){
    rewind(fp);

    if(fp == NULL){
        return;
    }

    char * buf;
    size_t n = 0;

    while(getline(&buf, &n, fp)){

        // Remove the \n at the end of buff
        buf[strlen(buf)-1] = '\0';

        // Search for :LAUNCH_ON_*
        if(!strncmp(buf, ":LAUNCH_ON_VICTORY=", 19) && victoryProg == NULL) {
           victoryProg = malloc(sizeof(char) * strlen(buf)-19+1); 
           strcpy(victoryProg, buf+19);
        }

        if(!strncmp(buf, ":LAUNCH_ON_COMPLETE=", 20) && completeProg == NULL) {
           completeProg = malloc(sizeof(char) * strlen(buf)-20+1); 
           strcpy(completeProg, buf+20);
           break;
        }

    }

    free(buf);

}

void setWordArr(char *words[]){
    wordArr = malloc(numWords * sizeof(char*));

    for(int i=0; i<numWords; i++) {
            // TODO replace numWords with wordsize
            *(wordArr+i) = malloc(sizeof(char) * numWords);
            strcpy(*(wordArr+i), *(words+i));
    }

}

void setVeryEasy() {

    char * words[] = {
        "FRIED",
        "TREES",
        "RIGID",
        "HIRED",
        "TRIES",
        "WRITE",
        "TRIED",
        "GREED",
        "DRIED",
        "BRAIN",
        "SKIES",
        "LAWNS",
        "GHOST",
        "CAUSE",
        "PAINT",
        "SHINY",
        "MAKES",
        "GAINS",
        "THIEF",
        "BASES",
        "RAISE",
        "REFER",
        "CARES",
        "TAKEN",
        "WAKES",
        "WAVES",
        "WARNS",
        "SAVES"
    };

    numWords = 28;

    wordsToChoose = 10;

    setWordArr(words);

}
void setEasy() {

    char * words[] = {
        "STATING",
        "HEALING",
        "COSTING",
        "REASONS",
        "SEASIDE",
        "SPARING",
        "CAUSING",
        "CRAFTED",
        "PRISONS",
        "PRESENT",
        "DEALING",
        "SETTING",
        "LEAVING",
        "VERSION",
        "DEATHLY",
        "BLAZING",
        "GRANITE",
        "TESTING",
        "TRAITOR",
        "STAMINA",
        "TRINITY",
        "CALLING",
        "TALKING",
        "ACQUIRE",
        "WELCOME",
        "DECRIES",
        "FALLING",
        "PACKING",
        "ALLOWED",
        "SELLING",
        "AFFRONT",
        "WALKING"
    };

    numWords = 32;

    wordsToChoose = 11;

    setWordArr(words);

}void setAverage() {

    char * words[] = {
        "CONQUORER",
        "CONSISTED",
        "WONDERFUL",
        "COMMITTEE",
        "SURRENDER",
        "SUBJECTED",
        "CONVICTED",
        "FORBIDDEN",
        "FORTIFIED",
        "COLLECTED",
        "CONTINUED",
        "PERIMETER",
        "SOUTHEAST",
        "RELEASING",
        "SOMETHING",
        "ACCEPTING",
        "MUTATIONS",
        "GATHERING",
        "LITERALLY",
        "REPAIRING",
        "INCESSANT",
        "INTERIORS",
        "REGARDING",
        "TELEPHONE",
        "OBTAINING",
        "EXTENSIVE",
        "DEFEATING",
        "REQUIRING",
        "UNLOCKING",
        "RECYCLING",
        "INSTINCTS",
        "BARTERING",
        "LEUTENANT",
        "COMMUNITY",
        "BATTERIES",
        "RECIEVING",
        "INCLUDING",
        "INITIALLY",
        "INVOLVING",
        "MOUNTAINS"
    };

    numWords = 40;

    wordsToChoose = 14;

    setWordArr(words);

}void setHard() {

    char * words[] = {
        "DISCOVERING",
        "ELIMINATING",
        "UNIMPORTANT",
        "MISTRUSTING",
        "MANUFACTURE",
        "RADIOACTIVE",
        "EXCLUSIVELY",
        "BOMBARDMENT",
        "DECEPTIVELY",
        "INDEPENDENT",
        "UNBELIEVERS",
        "EFFECTIVELY",
        "IMMEDIATELY",
        "INFESTATION",
        "DESCRIPTION",
        "INFORMATION",
        "REMEMBERING",
        "NIGHTVISION",
        "DESTRUCTION",
        "OVERLOOKING"
    };

    numWords = 20;

    wordsToChoose = 7;

    setWordArr(words);

}void setVeryHard() {

    char * words[] = {
        "INFILTRATION",
        "ORGANIZATION",
        "AUTHENTICITY",
        "APPRECIATION",
        "SPOKESPERSON",
        "LABORATORIES",
        "INITIATEHOOD",
        "SUBTERRANEAN",
        "PURIFICATION",
        "TRANSMISSION",
        "CIVILIZATION",
        "CONSTRUCTION",
        "RESURRECTION",
        "REPRIMANDING",
        "ACCOMPANYING",
        "OVERWHELMING",
        "CONVERSATION",
        "NORTHERNMOST",
        "TRANSCRIBING",
        "ANNOUNCEMENT",
        "SECLUTIONIST"
    };

    numWords = 21;

    wordsToChoose = 13;

    setWordArr(words);

}

char ** getWordArr(){
    return wordArr;
}

int getNumWords() {
    return numWords;
}

int getWordsToChoose() {
    return wordsToChoose;
}

int getWordLength() {
    return strlen(*wordArr);
}

char * getVictoryProg() {
    if(victoryProg == NULL)
        return "";
    return victoryProg;
}

char * getCompleteProg() {
    if(completeProg == NULL)
        return "";
    return completeProg;
}

void freeAll() {
    free(wordArr);
    free(victoryProg);
    free(completeProg);
}

// end
