#include "pipes.h"

int containsPipe(char *s)
{
  int len = strlen(s);
  int count = 0;
  int x;
  
  for(x = 0; x<len; x++)
  {
    if(s[x] == '|')
      count++;
  }

 // printf("There were %d Pipes\n", count);

  return count;
}// end containsPipe


char ** parsePrePipe(char *s, int * preCount)
{
    char ** argv = NULL;
    char * token = NULL, *save = NULL;
    char temp[100];

    strcpy(temp, s);

    token = strtok_r(temp, "|", &save);

    *preCount = makeargs(token, &argv);

    int x;

    for(x = 0; x<(*preCount); x++){
        printf("PrePipe - Array spot %d of %d - %s\n", x+1, (*preCount), argv[x]);
   }

    return argv;
}// end parsePrePipe

char ** parsePostPipe(char *s, int * postCount)
{
    char ** argv = NULL;
    char * token = NULL, *save = NULL;
    char temp[100];

    strcpy(temp, s);

    token = strtok_r(temp, "|", &save);
    token = strtok_r(NULL, "|", &save);

    *postCount = makeargs(token, &argv);

    int x;

    for(x = 0; x<(*postCount); x++) {
     printf("PostPipe - Array spot %d of %d - %s\n", x + 1, (*postCount), argv[x]);
     }

    return argv;
}// end parsePostPipe

char ** parsePostPipeDouble(char *s, int * postDoubleCount)
{
    char ** argv = NULL;
    char * token = NULL, *save = NULL;

    token = strtok_r(s, "|", &save);
    token = strtok_r(NULL, "|", &save);
    token = strtok_r(NULL, "|", &save);

    *postDoubleCount = makeargs(token, &argv);

    int x;


    for(x = 0; x<(*postDoubleCount); x++) {
     printf("PostPipe - Array spot %d of %d - %s\n", x + 1, (*postDoubleCount), argv[x]);
     }

    return argv;
}// end parsePostPipe

void pipeIt(char ** prePipe, char ** postPipe)
{
    pid_t pid;

    pid = fork();

    int status;

    if(pid != 0) // if 0 means its child and it will skip over - this only iterates if parent
    {
        waitpid(pid, &status, 0);
    }

    else
    {
        int fd[2], res;

        res = pipe(fd);

        if(res < 0)
        {
            printf("Pipe Failure\n");
            exit(-1);
        }// end if

        pid_t pid2 = fork(); // fork between child of a.out and grandchild of a.out

        if(pid2 != 0) // parent - read end of pipe "ls -l | wc -w" -- right half
        {
            close(fd[1]);
            close(0);
            dup(fd[0]);
            close(fd[0]);
            if(execvp(postPipe[0], postPipe) == -1) { // if back half of statement is bad this runs
                printf("Incorrect Command - Exiting now (-1)\n");
                exit(-1);
            }
        }// end if AKA parent

        else // child - write end of pipe
        {
            close(fd[0]);
            close(1);
            dup2(fd[1], 1);
            close(fd[1]);
            if(execvp(prePipe[0], prePipe) == -1) {
                printf("Incorrect Command - Exiting now (-1)\n");
                exit(-1);
            }
        }// end else AKA child

    }

}// end pipeIt

void pipeItDouble(char ** prePipe, char ** postPipe, char ** postPipeDouble)
{
    pid_t pid;

    pid = fork();

    int status;

    if(pid != 0) // if 0 means its child and it will skip over - this only iterates if parent
    {
        waitpid(pid, &status, 0); // only wait pid
    }

    else // A
    {
        int fd[2], res, fd2[2], res2;

        res = pipe(fd);

        if(res < 0)
        {
            printf("Pipe Failure\n");
            exit(-1);
        }// end if

        pid_t pid2 = fork(); // fork between child of a.out and grandchild of a.out // make B from A

        if(pid2 != 0) // parent - read end of pipe "ls -l | wc -w" -- right half - //A
        {
            close(fd[1]);
            close(0);
            dup2(fd[0], 0);
            close(fd[0]); //handle pipe A-B on A side
            if(execvp(postPipeDouble[0], postPipeDouble) == -1) {
                printf("Incorrect Command LAST- Exiting now (-1)\n");
                exit(-1);
            }
        }// end if AKA parent

        else // child - write end of pipe - //B - sort
        {
            pid_t pid3;

            res2 = pipe(fd2);

            if((pid3 = fork()) != 0) // parent (grandchild of a.out)
            {
                close(fd[0]);
                close(fd2[1]); //closing ends of pipes

                close(1);
                dup2(fd[1], 1);
                close(fd[1]); //handle pipe A-B connection on B side


                close(0); //handle pipe B-C connection on B side
                dup2(fd2[0], 0);
                close(fd2[0]);

                if(execvp(postPipe[0], postPipe) == -1) {
                    printf("Incorrect Command MIDDLE- Exiting now (-1)\n");
                    exit(-1);
                }

            }

            else //C
            {
                close(fd2[0]);
                close(1);
                dup2(fd2[1], 1);
                close(fd2[1]); //handle pipe A-B connection on B side
                if(execvp(prePipe[0], prePipe) == -1) {
                    printf("Incorrect Command START- Exiting now (-1)\n");
                    exit(-1);
                }
            }
        }// end else AKA child B

    }

}// end pipeIt



