#include <stdio.h>

#ifndef FILEPARSE_H
#define FILEPARSE_H

void readFile(FILE *fp);

char** getWordArr();

char* getDifficulty();

#endif
