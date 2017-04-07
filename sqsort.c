/*///////////////////////////////////////////
///										///
///	 sqsort.c for CS201 assignment 1	///
///										///
///		Dakota Turner February 2017		///

	main file for the 2nd cs project.
	scanner.c was written and provided
	by Dr. Lusth of the UA CS department
///										///
///////////////////////////////////////////*/
#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include <string.h>
#include "stack.h"
#include "queue.h"
#include "scanner.h"
#include "readIn.h"
#include "comparator.h"

typedef void (*Printer)(FILE *,void *);

Comparator comp;
Printer print;
Read read;

queue *sort(queue *, int *);

int main(int argc, char *argv[])
{
	FILE *fp = fopen(argv[2], "r");
	if(argc < 4)						//allows user input to dictate what the program will do
	{
		switch(argv[1][1])				//looks at a specific place on the command line
		{
			case 'd':
				comp = intComparator;
				print = displayInteger;
				read = readIntegers;
				break;
			case 'r':
				comp = realComparator;
				print = displayReal;
				read = readReals;
				break;
			case 's':
				comp = stringComparator;
				print = displayString;
				read = readStrings;
				break;
			case 'v':
				printf("Dakota Turner\n");
				return 0;
			default:
				printf("unknown flag '%s', valid flags are -d, -r, -s, and -v. \n", &argv[1][1]);
				return 0;
		}
	}

	queue *input = newQueue(print);	 //makes a new input queue depending on above call type

	if (argc >= 3)					//if input comes from a file
	{
		read(input,fp);					//declared read type allows calling from any above calls
		fclose(fp);
	}
	else if (argc < 3)				//if input comes from user
	{
		read(input, stdin);
	}
	else
	{
		printf("Invalid argument\n");
	}
	
	int usedStack = 1;
	int passes = 0;
	while (usedStack != 0)					//this is a check of the stack is used. If it is not, the list is sorted
	{
		usedStack = 0;
		//printf("\n");
		displayQueue(stdout,input);
		input = sort(input, &usedStack);
		++passes;
		// printf("\n");
	}
	if (passes == 1)						//if only one pass, display the input queue again
	{
		displayQueue(stdout, input);
		printf("\n");
	}
	//printf("\n");
	
}

queue *sort(queue *input, int *usedStack)	//sorting function
{
	stack *stack = newStack(print); //makes a new input queue depending on above call type
	queue *output = newQueue(print);//makes a new input queue depending on above call type

	while (sizeQueue(input))	//while the input queue is not empty
	{

		if (sizeStack(stack))	//as long as the stack is not empty
		{
			//handle the case with the most importance(stack -> output)
			if (comp(peekStack(stack), peekQueue(input)) > 0 || comp(peekStack(stack), peekQueue(input)) == 0) //stack[0] > input queue[0]
			{
				enqueue(output, pop(stack));
			}
			else if (comp(peekStack(stack), peekQueue(input)) < 0)	//if stack{0} < input{0}
			{
				void *deq = dequeue(input);

				if (sizeQueue(input) == 0)
				{
					enqueue(output, deq);
				}
				else	//if input =/= 0
				{
					if (comp(peekQueue(input), deq) >= 0) // if input{1}  < input{0}
					{
						*usedStack = *usedStack + 1;
						push(stack, deq);
					}
					else
					{
						enqueue(output, deq);	//if input{0} < input{1}
					}
				}
			}
		}
		else // stack == 0  
		{
			void *deq = dequeue(input);

			if (sizeQueue(input) == 0)
			{
				enqueue(output, deq);
			}
			else	//if input =/= 0
			{
				if (comp(deq, peekQueue(input)) < 0) // if input{1}  < input{0}
				{
					*usedStack = *usedStack + 1;
					push(stack, deq);
				}
				else
				{
					enqueue(output, deq);	//if input{0} < input{1}
				}
			}
		}
	}
	
	while (sizeStack(stack) != 0)
	{
		enqueue(output, pop(stack));
	}
	printf("\n");
	return output;
}