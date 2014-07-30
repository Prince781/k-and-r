// section 7.7
// ex. 7-8: write a program to print a set of files, starting each new one on a
// new page, with a title and a running page count for each file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXFILES	500
#define MAXLINE		10000	// max line size
#define BARLEN		80	// title bar length

static FILE *fp[MAXFILES];	// file pointers
static char *fn[MAXFILES];	// file names
static int nfs = 0;

int main(int argc, char *argv[]) {
	char *prog = argv[0], line[MAXLINE], bar[BARLEN], pgn[30];
	int page, slen;

	if (argc == 1) {
		fprintf(stderr, "Usage: %s [file...]\n", prog);
		exit(1);
	}
	for (; --argc > 0 && nfs < MAXFILES; ++nfs)
		if (!(fp[nfs] = fopen(fn[nfs] = *++argv,"r"))) {
			printf("%s: could not open %s\n", prog, fn[nfs]);
			exit(nfs+2);
		}
	memset(bar, '=', BARLEN);
	for (page=0; page<nfs; ++page) {
		sprintf(pgn, "page %d", page+1);
		slen = strlen(pgn);
		printf("\n%*s%s\n", (BARLEN-slen)/2, "", pgn);
		slen = strlen(fn[page]);
		slen = slen > BARLEN/2 ? BARLEN/2 : slen;
		printf("%.*s %.*s %.*s\n\n", (BARLEN-2-slen)/2, bar,
			slen, fn[page], (BARLEN-2-slen)/2, bar);
		while (fgets(line,MAXLINE,fp[page]) != NULL)
			printf("%s", line);
	}
	return 0;
}
