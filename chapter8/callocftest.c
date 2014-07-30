// section 8.7
// ex. 8-6: the standard library function calloc(n,size) returns a pointer to
// n objects of size _size_, with the storage initialized to zero. Write
// callocf, by calling mallocf or by modifying it.
#include <stdio.h>
#include "mallocf.h"

/* callocftest: compare uninitialized buffer data from callocf and mallocf */
int main() {
	int i, n;
	int *arr;

	printf("Enter length of array: ");
	scanf("%d", &n);

	if ((arr = (int*) callocf(n, sizeof(int))) == NULL) {
		fprintf(stderr, "Could not allocate buffer.\n");
		return 1;
	} else
		printf("Allocated buffer using callocf().\n");
	printf("Enter no more than %d numbers: ", n);
	for (i=0; i<n; ++i)
		if (scanf("%d", arr+i) == EOF)
			break;

	printf("Buffer: \n");
	for (i=0; i<n; ++i)
		printf("%.7d %c", arr[i], 8*i%80 > 8*(i+1)%80 ? '\n':'\0');
	
	if (8*n%80 > 0)
		printf("\n");

	freef(arr);
	printf("free()'d %lu bytes of data\n", n*sizeof(int));
	
	if ((arr = (int*) mallocf(n * sizeof(int))) == NULL) {
		fprintf(stderr, "Could not allocate buffer.\n");
		return 1;
	} else
		printf("Allocated buffer using mallocf().\n");
	
	printf("Buffer: \n");
	for (i=0; i<n; ++i)
		printf("%.7d %c", arr[i], 8*i%80 > 8*(i+1)%80 ? '\n':'\0');
	
	if (8*n%80 > 0)
		printf("\n");
	freef(arr);
	return 0;
}
