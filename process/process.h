#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void forkIt(char ** argv);
void forkItBackground(char ** argv);
void setPath(char * s);
int getHistCount(char * s1, char * s2);
int getHistFileCount(char * s1, char * s2);

#endif
