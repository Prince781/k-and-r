// section 4.11.3
// ex. 4-14: define a macro swap(t,x,y) that interchanges two arguments of
// type t (block structure will help)
#define swap(t, x, y) { t temp = x; x = y; y = temp; }
#include <stdio.h>

int main() {
	int a = 3, b = 4;
	swap(int, a, b);
	printf("a = %d, b = %d\n", a, b);
	return 0;
}
