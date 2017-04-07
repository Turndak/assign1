/*header component to readIn.c*/
#include <stdio.h>

#ifndef __READIN_INCLUDED__
#define __READIN_INCLUDED__

typedef void (*Read)(queue*, FILE*);

extern void readIntegers(queue *q, FILE *fp);
extern void readReals(queue *q, FILE *fp);
extern void readStrings(queue *q, FILE *fp);

#endif