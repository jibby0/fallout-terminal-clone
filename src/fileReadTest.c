#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp = fopen("wordList", "r");
    //int wordCount = 3; //TODO remove temp declaration
    int wordCount =0;
    int c;
    while ( (c=fgetc(fp)) != EOF)
        if (c == '\n')
            wordCount++;

    rewind(fp);

    printf("%d newlines\n", wordCount);


    char words[wordCount][15];

    int j=0;
    while (fgets(words[j], sizeof(words[j]), fp))
            j++;
    
    for(int i=0; i<wordCount; i++)
        printf("%d: %s",i,words[i]);

}
