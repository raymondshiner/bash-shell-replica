/**
 * @file linkedList.h
 * The basic doubly linked list that will be used during the course
 * of the quarter.  This linked list is written in a very generic fashion
 * where the appropriate function pointer for the specific type is passed
 * to the functions.
 *
 * @note This file will never be changed
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    void * data;
    struct node * next;
    struct node * prev;
};
typedef struct node Node;

struct linkedlist
{
    Node * head;
    int size;
};
typedef struct linkedlist LinkedList;

LinkedList * linkedList();

void addLast(LinkedList * theList, Node * nn);
void addFirst(LinkedList * theList, Node * nn);
//void removeFirst(LinkedList * theList, void (*removeData)(void *));
//void removeLast(LinkedList * theList, void (*removeData)(void *));
//void removeItem(LinkedList * theList, void * (*buildType)(FILE * stream), void (*removeData)(void *), int (*compare)(const void *, const void *));
void clearList(LinkedList * theList, void (*removeData)(void *));
void printList(const LinkedList * theList, void (*convertData)(void *));
char * findValueAlias(LinkedList * theList, char * dataToCheck);
void removeAlias(LinkedList * theList, char * dataToCheck);
void fillHistList(LinkedList * theList, FILE * fin);
void writeHist(LinkedList * theList, FILE * fin, int HISTFILECOUNT);
char * getLastHist(LinkedList * theList);
char * getNumHist(LinkedList * theList, int num);

#endif // LINKEDLIST_H
