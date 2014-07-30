// section 2.2
// ex 2-1: write a program to print the ranges of char, short, int, and long variables, both signed and unsigned, by printing appropriate values by direct computation
#include <stdio.h>

char char_min();
char char_max();
short short_min();
short short_max();
int int_min();
int int_max();
long long_min();
long long_max();

// direct computation version
int main() {
	printf("Ranges:\n");
	printf("char: [%d,%d] (signed) %d (unsigned)\n",
		char_min(), char_max(), ((unsigned char)-1));
	printf("short: [%d,%d] (signed) %d (unsigned)\n",
		short_min(), short_max(), ((unsigned short)-1));
	printf("int: [%d,%d] (signed) %u (unsigned)\n",
		int_min(), int_max(), ((unsigned int)-1));
	printf("long: [%ld,%ld] (signed) %lu (unsigned)\n",
		long_min(), long_max(), ((unsigned long)-1));
}

char char_min() {
	return -(((unsigned char)-1)/2) - 1;
}

char char_max() {
	return ((unsigned char)-1) / 2;
}

short short_min() {
	return -(((unsigned short)-1)/2) - 1;
}

short short_max() {
	return ((unsigned short)-1) / 2;
}

int int_min() {
	return -(((unsigned int)-1)/2) - 1;
}

int int_max() {
	return ((unsigned int)-1) / 2;
}

long long_min() {
	return -(((unsigned long)-1)/2) - 1;
}

long long_max() {
	return ((unsigned long)-1) / 2;
}
