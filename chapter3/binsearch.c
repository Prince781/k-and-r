// section 3.3
// ex. 3-1: our binary search makes two tests inside the loop, when one would
// suffice (at the price of more tests outside). Write a version with only one
// test inside the loop and measure the difference in run-time.
#include <stdio.h>

int binsearch(int, const int[], int);

int main() {
	int vals[10] = {0, 4, 19, 32, 44, 67, 88, 99, 102, 129};
	int length = 10, p, key = 99;
	p = binsearch(key, vals, length);
	printf("Found %d in array at position %d.\n", key, p);
	return 0;
}

// binsearch: find position of x in v, where n = length of v
int binsearch(int x, const int v[], int n) {
	int low, high, mid;
	
	low = 0;
	high = n-1;
	while ((mid=(low+high)/2) != low) {
		if (x < v[mid])
			high = mid - 1;
		else low = mid;
	}
	return v[low] == x ? high : (v[high] == x ? high : -1);
}
