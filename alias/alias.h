#ifndef ALIAS_H_
#define ALIAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../linkedlist/linkedList.h"

struct alias
{
   char * key;
   char * value;
};

typedef struct alias Alias;

void cleanTypeAlias(void * ptr);
void * buildTypeAlias(char * key, char * value);
void * buildTypeAliasFile(FILE * fin);
void printTypeAlias(void * passedIn);
int compareAliasKey(const void * p1, const void * p2);
int compareAliasValue(const void * p1, const void * p2);

//void * buildTypeAlias_Prompt();

#endif /* WORD_H_ */
