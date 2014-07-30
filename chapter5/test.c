
void testf(int[5]);	// array[5] of int
void testg(int *[]);	// array of pointer to int
void testh(int (*)[]);	// pointer to array of int
void testi(int (*[])(void));	// array of pointers to functions taking void
				// and returning int
void testj(int (*const[])(double));	// array of const pointers to functions
					// taking double and returning int
void testk(int (*const[])[]);	// array of const pointers to array of int

main() {}
