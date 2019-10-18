#ifndef WORD_H_
#define WORD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct word
{
   char * ltrs;
   int num;
};

typedef struct word Word;

void cleanTypeWord(void * ptr);
//void * buildTypeWord(FILE * fin);
void printTypeWord(void * passedIn);
//void * buildTypeWord_Prompt();
int compareWords(const void * p1, const void * p2);

#endif /* WORD_H_ */
