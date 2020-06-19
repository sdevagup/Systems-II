/*--------------------------------------------------------------------------*
 *----									----*
 *----		headers.h						----*
 *----									----*
 *----	    This file declares common headers used through-out the	----*
 *----	the singly-linked list sorting program.				----*
 *----									----*
 *----	----	----	----	----	----	----	----	----	----*
 *----									----*
 *----	Version 1a		2019 April 8		Joseph Phillips	----*
 *----									----*
 *--------------------------------------------------------------------------*/

#include	<stdlib.h>
#include	<stdio.h>
#include	"Node.h"

#ifndef _insertion_sort_h
#define _insertion_sort_h

struct Node* insertionSort(struct Node* nodePtr); 

#endif

#ifndef _merge_sort_h
#define _merge_sort_h
 
struct Node* mergeSort(struct Node* nodePtr); 
 
#endif


#ifndef _merge_sort_wrapper_h
#define _merge_sort_wrapper_h
 
 struct Node* mergeSortWrapper(struct Node* nodePtr); 
 
#endif

#ifndef _print_h
#define _print_h
 
void print(const struct Node* nodePtr); 

#endif
	  
