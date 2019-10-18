#include "linkedList.h"
#include "../alias/alias.h"
#include "../words/word.h"
#include "listUtils.h"
#include "../utils/myUtils.h"

LinkedList * linkedList()
{
    LinkedList * newList = (LinkedList*)calloc(1, sizeof(LinkedList));
    newList->head = (Node*)calloc(1, sizeof(Node));

    newList->size = 0;

    return newList;
}// end linkedList


void clearList(LinkedList * theList, void (*removeData)(void *))
{
    //below is Stu's code from whiteboard
    if(theList->size != 0) // if the list has any data
    {
        Node * cur = theList->head->next;
        Node * temp;
        while(cur != NULL)
        {
            temp = cur;
            cur = cur->next;
            removeData(temp->data); //cleans data in node
            temp->data = NULL;      // ^^
            free(temp);             // cleans the node
        }

        free(theList->head); // free dummy head node
        theList->head = NULL;

    }
}// end clearList

void printList(const LinkedList * theList, void (*printType)(void *))
{
    //below is stu's code from whiteboard
   if(theList->size == 0)
       printf("Empty List");

   else
   {
       Node * cur = theList->head->next;
       while(cur != NULL)
       {
           printType(cur->data);
           cur = cur->next;
       }

       printf("Thats all Folks\n");
   }

}// end printList

void addLast(LinkedList * theList, Node * nn)
{
    Node * cur = theList->head->next;
    Node * prev = theList->head;

    while(cur != NULL)
    {
        prev = cur;
        cur = cur->next;
    }
    //prev is now on last node in list, cur is null, this handles empty list

    prev->next = nn;
    nn->prev = prev;
    theList->size = theList->size + 1;
}// end addLast

void addFirst(LinkedList * theList, Node * nn)
{
    if(theList->size == 0)
    {
        theList->head->next = nn;
        nn->prev = theList->head;
    }

    else
    {
        Node * cur = theList->head->next;
        theList->head->next = nn;
        nn->prev = theList->head;
        nn->next = cur;
        cur ->prev = nn;
    }

    theList->size = theList->size + 1;
}// end addFirst


char * findValueAlias(LinkedList * theList, char * dataToCheck)
{
    Node * cur = theList->head->next;

    int x;

    for(x = 0; x<theList->size; x++)
    {
        Alias * myAlias = cur->data;

        if(strcmp(myAlias->key, dataToCheck) == 0)
            return myAlias->value;

        cur=cur->next;
    }

    return NULL;
}

void removeAlias(LinkedList * theList, char * dataToCheck)
{
    Node * cur = theList->head->next;

    int x;

    for(x = 0; x <theList->size; x++)
    {
        Alias * myAlias = cur->data;

        if(strcmp(myAlias->key, dataToCheck) == 0)
        {
            if(cur->next != NULL) //handles edge case of cur being last node in list - avoid NPException
                cur->next->prev = cur->prev;

            cur->prev->next = cur->next;
            cleanTypeAlias(cur->data);
            free(cur);
            cur = NULL;
            theList->size = theList->size -1;

            return;
        }

        cur=cur->next;
    }
}

void fillHistList(LinkedList * theList, FILE * fin)
{
    char * temp = (char*)calloc(100, sizeof(char));
    fgets(temp, 100, fin);
    strip(temp);
    int len = strlen(temp);

    int x = 1;

    while(!feof(fin))
    {
        Word * myWord = (Word*)calloc(1, sizeof(Word));

        myWord->ltrs = (char*)calloc(len+1, sizeof(char));

        strcpy(myWord->ltrs, temp);

        myWord->num = x;

        Node * myNode = buildNode_Type(myWord);

        addLast(theList, myNode);

        free(temp);

        temp = (char*)calloc(100, sizeof(char));
        fgets(temp, 100, fin);
        strip(temp);
        len = strlen(temp);
        x++;
    }

    free(temp);
}

void writeHist(LinkedList * theList, FILE * fin, int HISTFILECOUNT)
{
    Node * cur = theList->head->next;
    int x = 0;

    while(theList->size - x > HISTFILECOUNT)
    {
        cur = cur->next;
        x++;
    }

    while(cur != NULL)
    {
        Word * myWord = cur->data;

        fprintf(fin, "%s\n", myWord->ltrs);

        cur=cur->next;
    }
}

char * getLastHist(LinkedList * theList)
{
    int x;

    Node * cur = theList->head->next;

    for(x =0; x<theList->size-1; x++) //stoping -1 because dont wann get the command !!
    {
        cur = cur->next;
    }

    Word * myWord = cur->data;

    return myWord->ltrs;
}



char * getNumHist(LinkedList * theList, int num)
{
    int x;

    Node * cur = theList->head->next;

    for(x =0; x<num-1; x++) //stoping -1 because nums store starting at 1
    {
        cur = cur->next;
    }

    Word * myWord = cur->data;

    return myWord->ltrs;
}
/*

void removeLast(LinkedList * theList, void (*removeData)(void *))
{
    if(theList->size != 0)
    {
        Node * cur = theList->head->next;
        Node * prev = theList->head;

        while(cur->next != NULL)
        {
            prev = cur;
            cur = cur->next;
        }

        removeData(cur->data);
        cur->data = NULL;


        prev ->next = cur->next;
        cur->prev = NULL;

        theList->size = theList->size - 1;

        free(cur);
        cur = NULL;
    }

    else
    {
        printf("Empty List - Nothing Removed");
    }
}// end removeLast


void removeFirst(LinkedList * theList, void (*removeData)(void *))
{
    printf("inside of remove first\n");

    printf("the list size is - %d\n", theList->size);

    if(theList->size != 0)
    {
        printf("About to Break\n");
        Node *cur = theList->head->next;


        removeData(cur->data);
        cur->data = NULL;

        theList->head = cur->next;
        cur->next->prev = theList->head;

        theList->size = theList->size - 1;

        free(cur);
        cur = NULL;
    }

    else
    {
        printf("Empty List - Nothing Removed");
    }

}// end removeFirst


void removeItem(LinkedList * theList, void * (*buildType)(FILE * stream), void (*removeData)(void *), int (*compare)(const void *, const void *))
{
    if(theList->size != 0)
    {
        Node * cur = theList->head->next;
        void * itemToCheck = buildType(stdin);

        while(cur != NULL && compare(itemToCheck, cur->data) != 0)
        {
            cur = cur->next;
        }

        if(cur != NULL)
        {
            if(cur->next != NULL) //handles edge case of cur being last node in list - avoid NPException
                cur->next->prev = cur->prev;

            cur->prev->next = cur->next;
            removeData(cur->data);
            free(cur);
            cur = NULL;
            theList->size = theList->size -1;
        }

        else
        {
            printf("Item not found in List - No Changes\n");
        }

        removeData(itemToCheck);
        itemToCheck = NULL;
    }

    else
    {
        printf("Empty List - Nothing Removed");
    }

}// end removeItem */