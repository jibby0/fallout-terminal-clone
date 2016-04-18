// 
// File: wordParse.c 
// TODO_DOCS_ wordParse.c
// @author Joshua Bicking <jhb2345>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordParse.h"

char **wordArr;

int numWords;

int wordsToChoose;

void readFile(FILE* fp){

    if(fp == NULL) {
        setVeryEasy();
    }

    // TODO check if FalloutTerminal.cfg is invalid
    if(1){
        setVeryEasy();
    }

}

void setWordArr(char *words[]){
    wordArr = malloc(numWords * sizeof(char*));

    for(int i=0; i<numWords; i++) {
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

// end
