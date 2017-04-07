///////////////////////////////////////////
///										///
///		stack.c for CS201 assignment 0	///
///										///
///		Dakota Turner January 2017		///
///										///
///	 FIlO / LIFO stack implementation	///
///										///
///////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "dll.h"

stack *newStack(void (*d)(FILE *,void *))   //constructor
{
	stack *items = malloc(sizeof(stack));
	if(items == 0)
	{
		fprintf(stderr, "out of memory.");
		exit(-1);
	}

	items->list = newDLL(d);
	return items;
}

void push(stack *items,void *value)         //stores a generic value
{
	insertDLL(items->list, 0, value);
}

void *pop(stack *items)                     //returns a generic value
{
	return removeDLL(items->list, 0);
}

void *peekStack(stack *items)               //returns a generic value
{
	return getDLL(items->list, 0);
}

int sizeStack(stack *items)
{
	return sizeDLL(items->list);
}

void displayStack(FILE *fp,stack *items)
{
	displayDLL(fp, items->list);
}