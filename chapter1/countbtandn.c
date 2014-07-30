// section 1.5.3
// ex 1-8
#include <stdio.h>

// count blanks, tabs, newlines
main() {
	int bl = 0, tb = 0, nl = 0, c;

	while ((c = getchar()) != EOF) {
		if (c == ' ') ++bl;
		if (c == '\t') ++tb;
		if (c == '\n') ++nl;
	}

	printf("Blanks: %3d Tabs: %3d Newlines: %3d\n", bl, tb, nl);
}
