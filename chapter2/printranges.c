// section 2.2
// ex 2-1: write a program to print the ranges of char, short, int, and long variables, both signed and unsigned, by printing appropriate values from standard headers
#include <stdio.h>
#include <limits.h>

void print_data(char *, long, long);

int main() {
	printf("Data type limits:\n");
	printf("from limits.h ...\n");
	printf("signed:\n");
	print_data("char", SCHAR_MIN, SCHAR_MAX);
	print_data("short", SHRT_MIN, SHRT_MAX);
	print_data("int", INT_MIN, INT_MAX);
	print_data("long", LONG_MIN, LONG_MAX);
	printf("unsigned:\n");
	print_data("char", 0, UCHAR_MAX);
	print_data("short", 0, USHRT_MAX);
	print_data("int", 0, UINT_MAX);
	print_data("long", 0, ULONG_MAX);
	return 0;
}

void print_data(char *type, long min, long max) {
	printf("\t%s: [%ld,%lu]\n", type, min, max);
}
