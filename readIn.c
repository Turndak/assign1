/*/////////////////////////////////////////
/										///
/	 readIn.c for CS201 assignment 1	///
/										///
/		Dakota Turner February 2017		///
/										///
/////////////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "real.h"
#include <string.h>
#include "string.h"
#include "scanner.h"
#include "queue.h"
#include "stack.h"
#include "readIn.h"

void readIntegers(queue *q, FILE *fp)
{
	int x = readInt(fp);
	while (!feof(fp))
	{
		enqueue(q, newInteger(x));
		x = readInt(fp);
	}
}

void readReals(queue *q, FILE *fp)
{
	double x = readReal(fp); //from scanner
	while (!feof(fp))
	{
		enqueue(q, newReal(x)); //from users real.c/.h
		x = readReal(fp);
	}
}

void readStrings(queue *q, FILE *fp)
{
	char *x = readString(fp);
	while (!feof(fp))
	{
		enqueue(q, newString(x));
		x = readString(fp);
	}
}