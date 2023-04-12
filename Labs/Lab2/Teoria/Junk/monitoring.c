#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char *argv[]) {
	
	for (int i = 1; i <= 3; i++) {
		// Fokr and ignore fork failures.
		if (fork() == 0) {
			printf("Child %d, sleeps %d seconds... \n", getpid(), i);
			sleep(i);
			_exit(0);
		}
	}
	pid_t child;
	while ((child = wait(NULL)) != -1) 
		printf("wait() returned child %d\n", child);
	
	if (errno != ECHILD) 
		printf("(wait) An unexpectede error...\n");
}

