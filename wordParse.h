#include <stdio.h>

#ifndef FILEPARSE_H
#define FILEPARSE_H

typedef enum {ARROWS, WASD, HJKL} keyConfig_type;

void readWordsFromFile();

void readLaunches();

void readKeys();

void setVeryEasy();

void setEasy();

void setAverage();

void setHard();

void setVeryHard();

char** getWordArr();

int getNumWords();

int getWordsToChoose();

int getWordLength();

char * getVictoryProg();

char * getCompleteProg();

keyConfig_type getKeyConfig();

void freeAll();

#endif
