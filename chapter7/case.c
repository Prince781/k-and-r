// section 7.2
// ex. 7-1: write a program that converts upper case to lower case or lower
// case to upper, depending on the name it is invoked with, as found in argv[0]
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
 	int len = strlen(argv[0]),
		upper = 0, c;
	if (len < 7 || strcmp((*argv)+=len-7,"tolower")
		&& strcmp(*argv,"toupper")) {
		printf("Invalid invocation: rename to either \"toupper\" or "
			"\"tolower\"\n");
		return 1;
	} else if (strcmp(*argv, "toupper") == 0)
		upper = 1;
	while ((c = getchar()) != EOF)
		putchar(upper ? toupper(c) : tolower(c));
	return 0;
}
