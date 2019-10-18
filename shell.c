#include "./pipes/pipes.h"
#include "./linkedlist/linkedList.h"
#include "./linkedlist/listUtils.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./words/word.h"
#include "./alias/alias.h"
#include <limits.h>

int main()
{
  FILE * fin = fopen(".usshrc", "r");
  FILE * log = fopen(".ussh_history", "r");
  LinkedList * histLL = linkedList();

  char startDir[PATH_MAX];
  getcwd(startDir, sizeof(startDir));

    int check = 0;

  if(log != NULL)
  {
      fillHistList(histLL, log);
  }

  int HISTFILECOUNT;
  int HISTCOUNT;

  if(fin != NULL)
  {
      char temp1[100];
      char temp2[100];

      fgets(temp1, 100, fin);
      fgets(temp2, 100, fin);

      HISTFILECOUNT = getHistFileCount(temp1, temp2);
      HISTCOUNT = getHistCount(temp1, temp2);
      check =1;
  }

  else
  {
      HISTCOUNT = 1000;
      HISTFILECOUNT = 2000;
  }

  int argc, pipeCount;	
  char **argv = NULL, * s;
  int preCount = 0, postCount = 0, postDoubleCount = 0;
  char ** prePipe = NULL, ** postPipe = NULL, **postPipeDouble = NULL;

    char cwd[PATH_MAX]; // working directory thing
    getcwd(cwd, sizeof(cwd));

  s = (char*)calloc(MAX, sizeof(char));


    if(fin != NULL && !feof(fin))
    {
        fgets(s, MAX, fin);
    }

    else {
        printf("user@ussh- %s: ", cwd);
        fgets(s, MAX, stdin);
    }

  strip(s);

  LinkedList * aliasLL = linkedList();

  while(strcmp(s, "exit") != 0)
  {
      if(strcmp(s, "!!") != 0 && check == 0) {
          Word *theWord = (Word *) calloc(1, sizeof(Word));
          theWord->ltrs = (char *) calloc(strlen(s)+1, sizeof(char));
          strcpy(theWord->ltrs, s);
          theWord->num = histLL->size + 1;
          Node *theNode = buildNode_Type(theWord);
          addLast(histLL, theNode);
      }

      char * alias = findValueAlias(aliasLL, s);

      if(alias != NULL) {
          strcpy(s, alias);
      }

      int len = strlen(s);

    pipeCount = containsPipe(s);


    char* copy = (char*)calloc(len, sizeof(char)); //cd
    char* copy2 = (char*)calloc(len, sizeof(char)); //PATH=
    char* copy3 = (char*)calloc(len, sizeof(char)); //alias
    char* copy4 = (char*)calloc(len, sizeof(char)); //alias

    if(len >= 3)
        strncpy(copy, s, 3); //copy for cd check

    if(len >= 5)
        strncpy(copy2, s, 5); // copy for PATH= check

    if(len >=6)
        strncpy(copy3, s, 6); //copy for alias check

    if(len >= 8)
      strncpy(copy4, s, 8); //copy for unalias check



    if(len != 0 && s[len-1] == '&'){ //no mem leaks
        strncpy(copy, s, len-1);
        argc = makeargs(copy, &argv);
        if(argc != -1)
            forkItBackground(argv);

        clean(argc, argv);
        argv = NULL;
    }

    else if(len != 0 && strcmp(copy, "cd ") == 0) // cd leak free
    {
        char temp[100];
        strcpy(temp, s);
        char * save;
        char * token;

        strtok_r(temp, " ", &save);
        token = strtok_r(NULL, " ", &save);

        int num = chdir(token);

        if(num == -1)
            fprintf(stderr, "ussh: cd: %s: no such file or directory\n", token);

        getcwd(cwd, sizeof(cwd));
    }

    else if(len != 0 && strcmp(copy2, "PATH=") == 0) //leak free
    {
        char* sRest = (char*)calloc(len, sizeof(char));

        strncpy(sRest, s+5, len-5); //copy rest of s over after "PATH="

        setPath(sRest);

        free(sRest);
    }

    else if(len != 0 && strcmp(copy3, "alias ") == 0) //alias - leak free
    {
        char * tokenBad = strchr(s, ' ');
        char * token = (char*)calloc(strlen(tokenBad), sizeof(char));

        strncpy(token, tokenBad+1, strlen(tokenBad)-1);

        char * equals = strstr(token, "="); // equals is now pointing at the = in token
        int indexEquals = equals - token;
        char * key = (char*)calloc(indexEquals+1, sizeof(char));
        strncpy(key, token, indexEquals); //key is now correct

        char * alias = findValueAlias(aliasLL, key);

        if(alias != NULL) //item is found
        {
            removeAlias(aliasLL, key);
        }

        char * valueBad = strchr(token, '\"');
        char * value = (char*)calloc(strlen(valueBad), sizeof(char));
        strncpy(value, valueBad+1, strlen(valueBad)-2); //value is now correct

        Alias * myAlias = buildTypeAlias(key, value);//alias is correct

        Node * myNode = buildNode_Type(myAlias);

        addLast(aliasLL, myNode);

        free(token);
        free(key);
        free(value);
    }

    else if(len != 0 && strcmp(copy4, "unalias ") == 0) //unalias leak free
    {
        char * badToken = strchr(s, ' ');
        char * token = (char*)calloc(len, sizeof(char));

        strncpy(token, badToken+1, len-8);

        char * alias = findValueAlias(aliasLL, token);

        if(alias != NULL) //item is found
        {
            removeAlias(aliasLL, token);
        }

        else // item not found in list
        {
            printf("ussh: unalias: %s: not found\n", token);
        }

        free(token);
    }

    else if(len != 0 && strcmp(s, "history") == 0)
    {
        printList(histLL, printTypeWord);
    }

    else if(len != 0 && s[0] == '!' && len > 1)
    {
        if(s[1] == '!')
        {
            char * lastCommand = getLastHist(histLL);
            printf("%s\n", lastCommand);
            argc = makeargs(lastCommand, &argv);
            if(argc != -1)
                forkIt(argv);

            clean(argc, argv);
            argv = NULL;
        }

        else
        {
            int num = atoi(s+1);

            if(num == 0)
            {
                printf("ERROR - Number Required\n");
            }

            else if(num > HISTFILECOUNT)
            {
                printf("ERROR - History only saves the last %d Commands", HISTFILECOUNT);
            }

            else
            {
                char * theCommand = getNumHist(histLL, num);
                printf("%s\n", theCommand);
                argc = makeargs(theCommand, &argv);
                if(argc != -1)
                    forkIt(argv);

                clean(argc, argv);
                argv = NULL;
            }
        }
    }

	else if(pipeCount == 1) //leak free
	{
		prePipe = parsePrePipe(s, &preCount);
		postPipe = parsePostPipe(s, &postCount);
		pipeIt(prePipe, postPipe);
		clean(preCount, prePipe);
		clean(postCount, postPipe);
	}// end if pipeCount	  

    else if(pipeCount == 2) //leak free
    {
        prePipe = parsePrePipe(s, &preCount);
        postPipe = parsePostPipe(s, &postCount);
        postPipeDouble = parsePostPipeDouble(s, &postDoubleCount);
        pipeItDouble(prePipe, postPipe, postPipeDouble);
        clean(preCount, prePipe);
        clean(postCount, postPipe);
        clean(postDoubleCount, postPipeDouble);
    }

	else // regular command //leak free
	{
        argc = makeargs(s, &argv);
	  	if(argc != -1)
	  		forkIt(argv);
	  
	  	clean(argc, argv);
	  	argv = NULL;
	}

    if(fin != NULL && !feof(fin))
      {
          fgets(s, MAX, fin);
          strip(s);
          if(feof(fin))
          {
              printf("user@ussh- %s: ", cwd);
              fgets(s, MAX, stdin);
              strip(s);
              check = 0;
          }
      }

    else {
          printf("user@ussh- %s: ", cwd);
          fgets(s, MAX, stdin);
        strip(s);
      }


    free(copy);
    free(copy2);
    free(copy3);
    free(copy4);
  }// end while

  chdir(startDir);

  clearList(aliasLL, cleanTypeAlias);
  free(aliasLL->head);
  aliasLL->head = NULL;
  free(aliasLL);
  aliasLL = NULL;

  fclose(log);
  log = NULL;

  log = fopen(".ussh_history", "w");


  if(log != NULL && histLL->size > 0)
          writeHist(histLL, log, HISTFILECOUNT);

  fclose(log);
  log = NULL;


  clearList(histLL, cleanTypeWord);
  free(histLL->head);
  histLL->head = NULL;
  free(histLL);
  histLL = NULL;

  fclose(fin);
  fin = NULL;

  free(s);

  return 0;

}// end main

