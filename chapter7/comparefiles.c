// section 7.7
// ex. 7-6: write a program to compare two files, printing the first line where
// they differ.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE		1000

int filecmp(FILE *, FILE *, char *, char *);

int main(int argc, char *argv[]) {
	char *prog = argv[0];
	if (argc < 3) {
		printf("Usage: %s [file 1] [file 2]\n", prog);
		exit(1);
	}
	FILE *f1p, *f2p;
	char ln1[MAXLINE], ln2[MAXLINE], *f1n = argv[1], *f2n = argv[2];
	
	if ((f1p = fopen(*++argv, "r")) == NULL) {
		fprintf(stderr, "%s: cannot open %s\n", prog, *argv);
		exit(2);
	} else if ((f2p = fopen(*++argv, "r")) == NULL) {
		fprintf(stderr, "%s: cannot open %s\n", prog, *argv);
		exit(3);
	}

	if (filecmp(f1p, f2p, ln1, ln2)) {
		printf("%s: %s", f1n, ln1);
		printf("%s: %s", f2n, ln2);
	}

	fclose(f1p);
	fclose(f2p);
	exit(0);
}

// filecmp: compare files, return difference
int filecmp(FILE *f1p, FILE *f2p, char *ln1, char *ln2) {
	int cmp, stat1, stat2;

	do {
		stat1 = fgets(ln1, MAXLINE, f1p) != NULL;
		stat2 = fgets(ln2, MAXLINE, f2p) != NULL;
		if (cmp = strcmp(ln1,ln2))
			return cmp;
	} while (stat1 && stat2);
	return 0;
}
