#ifndef ALLOC_H
#define ALLOC_H

#include <stdio.h>
#define ALLOCSIZE	10000		// space
char *alloc(int);
void afree(char *);
void adelete(char *, int);

#endif
