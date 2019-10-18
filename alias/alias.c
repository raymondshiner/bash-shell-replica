#include "alias.h"
#include "../utils/myUtils.h"


void printTypeAlias(void * passedIn) //Done
{
  if(passedIn == NULL)
  {
    printf("passedIn is null - printTypeAlias - exiting now");
    exit(-99);
  }

  Alias * alias = (Alias*)passedIn;
  printf("this is an alias - key:%s - value:%s\n", alias->key, alias->value);

}// end printType

void * buildTypeAlias(char * key, char * value) //Done
{
    Alias * myAlias = (Alias*)calloc(1, sizeof(Alias));
    
    int lenK = strlen(key);
    int lenV = strlen(value);

    myAlias->key = (char*)calloc(lenK +1, sizeof(char));
    myAlias->value = (char*)calloc(lenV +1, sizeof(char));
    strcpy(myAlias->key, key);
    strcpy(myAlias->value, value);
     
    return (void*)myAlias;
}// end buildType

void * buildTypeAliasFile(FILE * fin) //Done
{
    if(fin == NULL)
    {
        printf("fin is null - buildTypeAlias - exiting now");
        exit(-99);
    }

    char key[100];
    char value[100];

    Alias * myAlias = (Alias*)calloc(1, sizeof(Alias));

    fgets(key, 100, fin);//grab Alias
    fgets(value, 100, fin);
    strip(key);
    strip(value);

    int lenK = strlen(key);
    int lenV = strlen(value);

    myAlias->key = (char*)calloc(lenK+1, sizeof(char));
    myAlias->value = (char*)calloc(lenV+1, sizeof(char));
    strcpy(myAlias->key, key);
    strcpy(myAlias->value, value);

    return (void*)myAlias;
}// end buildType

int compareAliasKey(const void * p1, const void * p2)
{
   if(p1 == NULL || p2 == NULL)
   {
      printf("p1 or p2 is null - compareAliass - exiting now");
      exit(-99);
   }
   
   Alias * alias1 = (Alias*)p1;
   Alias * alias2 = (Alias*)p2;
   
   return strcmp(alias1->key, alias2->key);
}// end compare

int compareAliasValue(const void * p1, const void * p2)
{
    if(p1 == NULL || p2 == NULL)
    {
        printf("p1 or p2 is null - compareAliass - exiting now");
        exit(-99);
    }

    Alias * alias1 = (Alias*)p1;
    Alias * alias2 = (Alias*)p2;

    return strcmp(alias1->value, alias2->value);
}// end compare


void cleanTypeAlias(void * ptr)
{
  if(ptr == NULL)
  {
    printf("passedIn is null - cleanTypeAlias - exiting now");
    exit(-99);
  }

  Alias * myAlias = (Alias*)ptr;
  
  free(myAlias->key);
  myAlias->key = NULL;

  free(myAlias->value);
  myAlias->value = NULL;

  free(myAlias);
  myAlias = NULL;
}// end cleanType





/*
void * buildTypeAlias_Prompt()
{
    char temp[100];
    int lens;

    Alias * myAlias = (Alias*)calloc(1, sizeof(Alias));

    printf("Please enter a Alias - ");
    fgets(temp, 100, stdin);//grab Alias
    strip(temp);

    myAlias->ltrs = (char*)calloc(strlen(temp)+1, sizeof(char));
    strcpy(myAlias->ltrs, temp);
    lens = strlen(temp);

    myAlias->len = lens;

    return (void*)myAlias;
}// end buildType_Prompt
*/