// section 8.7
// ex. 8-8: write a routine bfreef(p,n) that will free an arbitrary block p of
// n characters into the free list maintained by mallocf and freef. By using
// bfreef, a user can add a static or external array to the free list at any
// time.
#include <stdio.h>
#include <string.h>
#include "mallocf3.h"

#define SARRSIZ	80
#define STRSIZ	30

// test overwritten data with bfreef()
int main() {
	static char sarr[SARRSIZ];
	char *sarr_ptr = __ptralign(sarr,HSIZE) + HSIZE;	// new pointer
	char *str = mallocf(STRSIZ);
	int i;

	strncpy(str, "This is a test.", STRSIZ);
	str[STRSIZ-1] = '\0';
	strncpy(sarr, "This is data from a static array.", SARRSIZ);
	sarr[SARRSIZ-1] = '\0';

	printf("str = %s\n", str);
	printf("sarr position = %p (%s)\n", sarr,
		(unsigned long)sarr%HSIZE ? "unaligned" : "aligned");
	printf("sarr = %s\n", sarr);
	bfreef(sarr, SARRSIZ);
	freef(str);
	printf("sarr = %s\n", sarr);
	printf("sarr_ptr position = %p\n", sarr_ptr);

	printf("sarr =\n");
	for (i=0; i<SARRSIZ; ++i)
		printf("0x%02x%c", (unsigned char) sarr[i],
			(i+1)*5%80 ?' ' : '\n');	

	while (str != sarr_ptr)	// assumption is that sarr size % 16 == 0
		str = mallocf(SARRSIZ-HSIZE);	// egregious memory leak
	printf("found str = sarr_ptr\n");
	strncpy(str, "This is data that overwrites static data.",
		SARRSIZ-HSIZE);
	str[SARRSIZ-HSIZE-1] = '\0';

	printf("str = %s\n", str);
	printf("sarr =\n");
	for (i=0; i<SARRSIZ; ++i)
		printf("0x%02x%c", (unsigned char) sarr[i],
			(i+1)*5%80 ?' ' : '\n');
	freef(str);
	return 0;
}
