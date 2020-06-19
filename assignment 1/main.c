*--------------------------------------------------------------------------*
 *----									----*
 *----		main.c							----*
 *----									----*
 *----	    This file defines the main functions for a program that	----*
 *----	sorts a linked list of randomly-generated integers.		----*
 *----									----*
 *----	----	----	----	----	----	----	----	----	----*
 *----									----*
 *----	Version 1a		2019 April 8		Joseph Phillips	----*
 *----									----*
 *--------------------------------------------------------------------------*

#include "headers.h"

#define TEXT_LEN 256
#define NUM_NUMBERS 65536

int numNumbers = NUM_NUMBERS;
struct Node* createList(int length)
{
  if (length == 0)
  {
    return(NULL);
  }

 struct Node* startPtr = (struct Node*)malloc(sizeof(struct Node));
 struct Node* endPtr = startPtr;

 startPtr->value_ = rand() % 4096;
 startPtr->nextPtr_ = NULL;

 for(length--;length > 0;length--)
  {
    endPtr->nextPtr_ = (struct Node*)malloc(sizeof(struct Node));
    endPtr->nextPtr_->value_ = rand() % 4096;
    endPtr->nextPtr_->nextPtr_  = NULL;
    endPtr = endPtr->nextPtr_;
  }

  return(startPtr);
}
void print(const struct Node* nodePtr)
{
  const struct Node* x = nodePtr;
  if(!nodePtr)
  return;
   // till there are nodes left to be convered
   while(x != NULL)
      {
     // print current node value
     printf("%d ", x->value_);
    // move to next node
     x = x->nextPtr_;
      }
     }
void freeList(struct Node* nodePtr)
{
  struct Node* nextPtr;

  for  ( ; nodePtr != NULL;  nodePtr = nextPtr)
  {
    nextPtr = nodePtr->nextPtr_;
    free(nodePtr);
  }
}
int main()
{
  int   choice;
  struct Node *nodePtr  = createList(NUM_NUMBERS);

  print(nodePtr);

  do
  {
    char text[TEXT_LEN];
    printf
        ("How do you want to sort %d numbers?\n"
         "(1) Insertion sort\n"
         "(2) Merge sort\n"
         "Your choice (1 or 2)? ",
         NUM_NUMBERS
        );
    fgets(text,TEXT_LEN,stdin);
    choice = strtol(text,NULL,10);
  }
  while( (choice < 1) || (choice > 2) );
  switch (choice)
  {
  case 1 :
    nodePtr = insertionSort(nodePtr);
    break;
  case 2 :
    nodePtr = mergeSortWrapper(nodePtr);
    break;
 }
  freeList(nodePtr);
  return(EXIT_SUCCESS);
}
