#include <stdio.h>
#include <stdlib.h>

#define __psize(p)	(*(size_t *)((void *)p - sizeof(size_t)) \
 & (~0lu << 1))

int main() {
	char *p = malloc(200);

	printf("p at %p\n", p);
	printf("allocated %zu bytes\n", __psize(p));
	
	return 0;
}
