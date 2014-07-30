// section 5.11
// swap program
#include "swap.h"

// general swap
void swap(void *v[], int a, int b) {
	void *temp = v[a];
	v[a] = v[b];
	v[b] = temp;
}
