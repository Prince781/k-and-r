#ifndef DIRENTF_H
#define DIRENTF_H

#define DBUF_SIZ	1024	// buffer of dir entries
#define NAME_MAX	14	// longest filename component, system-dependent
#define MAX_PATH	4096	// max path size

typedef struct {		// portable directory entry
	long ino;		// inode number
	char name[NAME_MAX+1];	// name + '\0' terminator
} Dirent;

typedef struct {		// minimal DIR
	int fd;			// file descriptor for directory
	int bp;			// current buffer position
	int nr;			// number of read bytes of data
	char *buf;		// buffer of entry data
	Dirent d;		// the directory entry
} DIR;

DIR	*opendirf	(char *dirname);
Dirent	*readdirf	(DIR *dp);
void	closedirf	(DIR *dp);

#endif
