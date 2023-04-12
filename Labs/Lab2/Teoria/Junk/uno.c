#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main (void) {
	// We close STDOUT which has file descriptor 1 The remaining
	// file descriptors have index 0 (STDIN) and 2 (STDERR).
	close(STDOUT_FILENO); // or close(1)
	// We open a new file, to which will be assigned file descriptor 1
	// automatically because it is the lowest available index in the table.
	int fd = open("unotxt.txt", O_TRUNC | O_CREAT | O_WRONLY, S_IRWXU);
	printf("Hello, World!\n");
	return 0;
}
