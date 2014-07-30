#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "dirf.h"
#include <sys/syscall.h>
#include <sys/stat.h>
#include "direntf.h"

void printdata(char *);

// opendirf: open directory
DIR *opendirf(char *dirname) {
	int fd;
	struct stat stbuf;
	DIR *dp;

	// O_DIRECTORY may be Linux-only
	if ((fd = open(dirname, O_RDONLY | O_DIRECTORY, 0)) == -1
	 || fstat(fd, &stbuf) == -1
	 || (stbuf.st_mode & S_IFMT) != S_IFDIR
	 || (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
		return NULL;
	dp->fd = fd;
	dp->bp = dp->nr = 0;
	dp->buf = NULL;
	return dp;
}

// readdirf: read directory entries in sequence
Dirent *readdirf(DIR *dp) {
	struct linux_dirent *ld;
	static Dirent d;

	if (dp->buf == NULL
	 && (dp->buf = (char *) malloc(DBUF_SIZ)) == NULL)
		return NULL;

	if (dp->bp >= dp->nr) {	// fill buffer if necessary
		dp->nr = syscall(SYS_getdents, dp->fd, dp->buf, DBUF_SIZ);
		dp->bp = 0;
	}
	while (dp->bp < dp->nr) {	// loop until we find a valid entry
		ld = (struct linux_dirent *) (dp->buf + dp->bp);
		dp->bp += ld->d_reclen;	// move to next position
		if (ld->d_ino == 0)	// slot not in use
			continue;
		d.ino = ld->d_ino;
		strncpy(d.name, ld->d_name, DIRSIZ-1);
		strcat(d.name, "\0");
		return &d;
	}
	if (dp->nr > 0)
		return readdirf(dp);
	else return NULL;	// end of stream or error
}

// closedirf: close directory opened by opendirf
void closedirf(DIR *dp) {
	if (dp) {
		close(dp->fd);
		free(dp->buf);
		free(dp);
	}
}

void printdata(char *d) {
	while (*d)
		printf("%08x ", (unsigned) *d++);
}
