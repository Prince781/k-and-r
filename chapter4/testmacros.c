// macros
#include <stdio.h>
#define square(x) x * x
#define max(a, b) (a > b ? a : b)
#define getvar(name, num) name ## num

main() {
	int i = 3, j = 4;
	printf("%d\n", square(3+1));
	printf("%d\n", max(i++,j++));
	printf("i = %d, j = %d\n", i, j);
	int val1 = 10, val2 = 3;
	printf("val1 = %d, val2 = %d\n", getvar(val, 1), getvar(val, 2));
}	
