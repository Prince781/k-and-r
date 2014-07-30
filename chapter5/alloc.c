// alloc, section 5.5
#include "alloc.h"

static char allocbuf[ALLOCSIZE];	// storage buffer
static char *allocp = allocbuf;		// next free position

// alloc: allocate memory
char *alloc(int size) {
	if (allocp + size < allocbuf + ALLOCSIZE) {
		allocp += size;
		return allocp - size;
	} else return NULL;
}

// afree: free memory up to position p
void afree(char *p) {
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

// adelete: free used memory from p to p+size; shift
void adelete(char *p, int size) {
	if (p >= allocbuf && p + size <= allocp) {
		for (; p + size < allocp; ++p)
			*p = p[size];
		allocp -= size;
	} else printf("adelete: pointer outside of bounds\n");
}
