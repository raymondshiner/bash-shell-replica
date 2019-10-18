#ifndef PIPES_H
#define PIPES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../tokenize/makeArgs.h"

int containsPipe(char *s);
char ** parsePrePipe(char *s, int * preCount);
char ** parsePostPipe(char *s, int * postCount);
char ** parsePostPipeDouble(char *s, int * postDoubleCount);
void pipeIt(char ** prePipe, char ** postPipe);
void pipeItDouble(char ** prePipe, char ** postPipe, char ** postPipeDouble);


#endif 
