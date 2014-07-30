// section 1.5.3
#include <stdio.h>

// copy input to output; replace tabs, backspaces, and backslashes
// by '\t', '\b', and '\\'

main() {
	int c;
	
	while ((c = getchar()) != EOF) {
		if (c == '\t') printf("\\t");
		else if (c == '\b') printf("\\b");
		else if (c == '\\') printf("\\\\");
		else putchar(c);
	}
}
