// section 8.7
// ex. 8-7: malloc accepts a size request without checking its plausibility;
// free believes that the block it is asked to free contains a valid size
// field. Improve these routines so they take more pains with error checking.
#include <stdio.h>
#include <string.h>
#include "mallocf.h"

#define CBUFSIZE	100

int main() {
	char buf_s[] = "This is data from static storage.",
		*buf_d;
	
	printf("%s\n", buf_s);

	buf_d = (char *) mallocf(CBUFSIZE);
	strcpy(buf_d, "This is data from dynamic storage.");

	printf("%s\n", buf_d);

	freef(buf_d);
	printf("freef()'d pointer\n");

	freef(NULL);		// should give error
	freef((void *)1);	// should give error
	
	Header *p = mallocf(10);
	unsigned ssize = (p-1)->s.size;
	(p-1)->s.size = 1000000000;
	freef(p);		// should give error
	(p-1)->s.size = ssize;
	freef(p);		// should not give error
	printf("freef()'d pointer\n");
	return 0;
}
