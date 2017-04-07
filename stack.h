///////////////////////////////////////////
///										///
///		stack.h for CS201 assignment 0	///
///										///
///		Dakota Turner January 2017		///
///										///
///	 Header file for the stack.c file 	///
///										///
///////////////////////////////////////////
#include "dll.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef __STACK_INCLUDED__
#define __STACK_INCLUDED__

typedef struct stack
{
	dll *list;
}stack; 


extern stack *newStack(void (*d)(FILE *,void *));   //constructor
extern void push(stack *items,void *value);         //stores a generic value
extern void *pop(stack *items);                     //returns a generic value
extern void *peekStack(stack *items);               //returns a generic value
extern int sizeStack(stack *items);
extern void displayStack(FILE *,stack *items);

#endif