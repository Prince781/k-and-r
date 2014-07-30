// cp example using UNIX system calls
#include <fcntl.h>

#define BUFSIZE	1024
#define PERMS	0666	// permissions for copy-to file

int main(int argc, char *argv[]) {
	int fd1, fd2;
	int n;
	char buf[BUFSIZE];

	if (argc != 3) {
		write(1, "Usage: cp [file1] [file2]\n", 26);
		return 1;
	} else if ((fd1=open(*++argv, O_RDONLY, 0)) == -1) {
		write(1, "cp: could not open file 1\n", 26);
		return 1;
	} else if ((fd2=creat(*++argv, PERMS)) == -1) {
		write(1, "cp: could not create file 2\n", 28);
		return 1;
	} else
		while ((n=read(fd1, buf, BUFSIZE)) > 0)
			if (write(fd2, buf, n) == -1)
				write(1, "cp: write error\n", 16);
	if (n == -1) {
		write(1, "cp: read error\n", 15);
		return 1;
	}
	return 0;
}
