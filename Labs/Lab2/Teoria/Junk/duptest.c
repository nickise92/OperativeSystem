#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void) {
	// FileDescriptionTable: [0, 1, 2] -> [0, 2]
	close(STDOUT_FILENO);
	// FDT: [0, 2] -> [0]
	close(STDERR_FILENO);
	// FDT: [0] -> [0, 1]
	int fd = open("duptest.txt", O_TRUNC | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	// FDT: [0, 1] -> [0, 1, 2]
	int fd2 = dup(fd);
	// FDT: [0: STDIN, 1: duptest.txt, 2: duptest.txt]
	printf("Have a good ");
	fflush(stdout);
	fprintf(stderr, "day!\n");

	close(fd);
	close(fd2);
	return 0;
}
