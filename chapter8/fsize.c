// section 8.6
// ex. 8-5: modify the fsize program to print the other information contained
// in the inode entry.
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include "direntf.h"

#define MOD_LEN	25
#define MAXUSER		21	// username length
static char lastmod[MOD_LEN],
	lastacc[MOD_LEN],
	ilastch[MOD_LEN],	// inode last changed
	usrname[MAXUSER];

void fsize(char *);
void dirwalk(char *, void (*)(char *));

// fsize: print file sizes
int main(int argc, char *argv[]) {
	printf("%8s   %-*s   %-*s   %-*s %-5s   %-*s   %s\n",
		"size (B)", MOD_LEN-1, "last modified",
		MOD_LEN-1, "last accessed", MOD_LEN-1, "inode last changed",
		"# links", MAXUSER-1, "owner", "name");
	if (argc == 1)
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}

// fsize: print size and other information about file
void fsize(char *name) {
	struct stat stbuf;
	struct passwd *uinfo;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	
	lastmod[0] = lastacc[0] = ilastch[0] = '\0';
	strftime(lastmod, MOD_LEN, "%c", localtime(&stbuf.st_mtime));
	strftime(lastacc, MOD_LEN, "%c", localtime(&stbuf.st_atime));
	strftime(ilastch, MOD_LEN, "%c", localtime(&stbuf.st_ctime));
	if ((uinfo = getpwuid(stbuf.st_uid)) != NULL) {
		strncpy(usrname, uinfo->pw_name, MAXUSER-1);
		strcat(usrname, "\0");
	} else *usrname = '\0';
	printf("%8ld | %-*s | %-*s | %-*s | %-.5ld | %-*s | %s\n",
		stbuf.st_size, MOD_LEN-1, lastmod, MOD_LEN-1, lastacc,
		MOD_LEN-1, ilastch,
		stbuf.st_nlink, MAXUSER-1, usrname, name);
}

void dirwalk(char *dir, void (*fcn)(char *)) {
	char name[MAX_PATH];
	Dirent *dp;
	DIR *dfd;

	if ((dfd = opendirf(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdirf(dfd)) != NULL) {
		if (!strcmp(dp->name, ".") || !strcmp(dp->name, ".."))
			continue;
		if (strlen(dir) + strlen(dp->name) + 2 > MAX_PATH)
			fprintf(stderr, "dirwalk: name %s/%s too long\n",
				dir, dp->name);
		else {
			if (*dir == '.' && dir[1] == '\0')
				sprintf(name, "%s", dp->name);
			else
				sprintf(name, "%s/%s", dir, dp->name);
			(*fcn)(name);
		}
	}
	closedirf(dfd);
}
