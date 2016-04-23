#include <stdio.h>

#ifndef FILEPARSE_H
#define FILEPARSE_H

void readWordsFromFile(FILE *fp);

void setVeryEasy();

void setEasy();

void setAverage();

void setHard();

void setVeryHard();

char** getWordArr();

int getNumWords();

int getWordsToChoose();

int getWordLength();

void freeWordArr();

#endif
