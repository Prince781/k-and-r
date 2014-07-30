// section 7.7
// ex. 7-7: modify the pattern finding program of Chapter 5 to take its input
// from a set of named files or, if no files are named as arguments, from the
// standard input. Should the file name be printed when a matching line is
// found?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE		50000
#define MAXFILE		500	// maximum number of file arguments to take

// find: find pattern matches
int main(int argc, char *argv[]) {
	FILE *fps[MAXFILE];
	char *fname[MAXFILE];
	int nfs, c;
	int except = 0, number = 0;	// options
	char *prog = argv[0], *pattern, line[MAXLINE];
	unsigned long ln = 0;
	
	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				fprintf(stderr, "find: illegal option %c\n",c);
				argc = 0;
				break;
			}
	if (argc == 0) {
		fprintf(stderr, "Usage: %s -x -n [pattern] [file...]\n", prog);
		exit(-1);
	}

	pattern = *argv;
	for (nfs=0; --argc > 0 && nfs < MAXFILE; ++nfs)
		if ((fps[nfs]=fopen(fname[nfs]=*++argv, "r")) == NULL) {
			printf("%s: could not open %s\n", prog, argv[-1]);
			exit(nfs);
		}

	if (nfs == 0) {
		for (ln=1; fgets(line, MAXLINE, stdin) != NULL; ln++)
			if (!strstr(line,pattern) == except) {
				if (number)
					printf("%lu:", ln);
				printf("%s", line);
			}
	} else
		while (nfs-- > 0) {
			printf("%s:\n", fname[nfs]);
			for (ln=1; fgets(line,MAXLINE,fps[nfs]) != NULL; ln++)
				if (!strstr(line,pattern) == except) {
					if (number)
						printf("%lu: ", ln);
					printf("%s", line);
				}
		}
	return 0;
}
