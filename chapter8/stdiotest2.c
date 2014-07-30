// ex. 8-4: the standard library function
//	int fseekf(FILE *fp, long offset, int origin)
// is identical to lseek except that fp is a file pointer instead of a file
// descriptor and the return value is an int status, not a position. Write
// fseek. Make sure that your fseek coordinates properly with the buffering
// done for the other functions of the library.
#include "stdiof.h"

// copy file to stdout, then print last 10 chars
int main() {
	int c;
	FILE *fp;
	
	if (!(fp = fopenf("test.txt", "a"))) {
		fputsf("Error opening test.txt\n", stderr);
		return 1;
	} else
		fputsf("Successfully opened test.txt for writing\n", stdout);
	fflushf(stdout);

	fputsf("This is data that was once in the buffer.", fp);
	fseekf(fp, 7, SEEK_SET);	// after "is"
	fputsf(" an example of new data.", fp);
	
	fflushf(stdout);
	fclosef(fp);

	fputsf("testing\n", stdout);
	fflushf(stdout);
	// read test
	if (!(fp = fopenf("test.txt", "r"))) {
		fputsf("Error opening test.txt again\n", stderr);
		return 1;
	} else
		fputsf("Successfully opened test.txt for reading\n", stdout);
	fputsf("Reading on from 42nd position in file\n", stdout);
	fflushf(stdout);
	fseekf(fp, 42, SEEK_SET);
	while ((c = getcf(fp)) != EOF)
		putcharf(c);	// copy to stdout
	fputsf("\nend of file\n", stdout);
	
	fflushf(stdout);
	fclosef(fp);
	return 0;
}


