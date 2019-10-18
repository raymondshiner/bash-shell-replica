#include "word.h"
#include "../utils/myUtils.h"


void printTypeWord(void * passedIn)
{
  if(passedIn == NULL)
  {
    printf("passedIn is null - printTypeWord - exiting now");
    exit(-99);
  }

  Word * word = (Word*)passedIn;
  printf("%d - %s\n", word->num, word->ltrs);

}// end printType
/*
void * buildTypeWord(FILE * fin, int num)
{
    if(fin == NULL)
    {
      printf("fin is null - buildTypeWord - exiting now");
      exit(-99);
    }

    char temp[100];

    Word * myWord = (Word*)calloc(1, sizeof(Word));

    fgets(temp, 100, fin);//grab word
    strip(temp);
    
    int len = strlen(temp);

    myWord->ltrs = (char*)calloc(len+1, sizeof(char));
    strcpy(myWord->ltrs, temp);

    myWord->num = num;
     
    return (void*)myWord;
}// end buildType

void * buildTypeWord_Prompt()
{
    char temp[100];
    int lens;

    Word * myWord = (Word*)calloc(1, sizeof(Word));

    printf("Please enter a word - ");
    fgets(temp, 100, stdin);//grab word
    strip(temp);

    myWord->ltrs = (char*)calloc(strlen(temp)+1, sizeof(char));
    strcpy(myWord->ltrs, temp);
    lens = strlen(temp);

    myWord->len = lens;

    return (void*)myWord;
}// end buildType_Prompt

*/
int compareWords(const void * p1, const void * p2)
{
   if(p1 == NULL || p2 == NULL)
   {
      printf("p1 or p2 is null - compareWords - exiting now");
      exit(-99);
   }
   
   Word * word1 = (Word*)p1;
   Word * word2 = (Word*)p2;
   
   return strcmp(word1->ltrs, word2->ltrs);
}// end compare


void cleanTypeWord(void * ptr)
{
  if(ptr == NULL)
  {
    printf("passedIn is null - cleanTypeWord - exiting now");
    exit(-99);
  }

  Word * myWord = (Word*)ptr;

  free(myWord->ltrs);
  myWord->ltrs = NULL;
  
  free(myWord);
  myWord = NULL;
}// end cleanType
