// section 8.6
// ex. 8-2: rewrite fopen and _fillbuf with fields instead of explicit bit
// operations. Compare code size and execution speed.
// ex. 8-3: design and write _flushbuf, fflush, and fclose.
#include "stdiof.h"

// cat example: copy from stdin to stdout
int main() {
	int c;

	while ((c = getcharf()) != EOF)
		putcharf(c);

	fclosef(stdout);	// flush and close
	return 0;
}
