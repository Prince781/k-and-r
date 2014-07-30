// test mallocf
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
	return 0;
}
