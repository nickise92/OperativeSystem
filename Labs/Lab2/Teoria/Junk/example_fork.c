#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	int stack = 111;
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
	}
	// Both parent and child come from here 
	if (pid == 0) { /* This is the CHILD */
		stack = stack * 4;
		printf("I'm the CHILD, my PID is %d, my parent PID is: %d \n", getpid(), getppid());
	} else {
		printf("I'm the PARENT, my PID is %d, my parent PID is: %d \n", getpid(), getppid());
	}
	printf("\t%s stack %d\n", (pid==0) ? "(child)" : "(parent)", stack);
	return 0;
}	
