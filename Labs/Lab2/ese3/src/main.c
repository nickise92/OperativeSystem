
/**
 * Modificare il programma dell’ “Ese_2” affinche’ il processo parent attenda solo la
 * terminazione dell’ultimo figlio creato. L’attesa deve avvenire in modalità polling!
 */
#include "errExit.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SZ 150

int main(int argc, char *argv[]) {

    // check command line input arguments
    if (argc != 2) {
        printf("Usage: %s numSubProcess\n", argv[0]); // argv[0] contiene il nome del programma stesso
        return(0);
    }
    
    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("The number of subprocess must be > 0\n");
        exit(1);
    }

    // init. seed for rand function
    srand(time(0));

    pid_t pid;
    for (int i = 0; i < n; i++) {
        // generate a rand number for the subprocess
        int code = (int)(((double)rand() / RAND_MAX) * 200);

        // generate a subprocess
        pid = fork();
        if (pid == -1) {
            printf("Child %d not created.\n", i);
        } else if (pid == 0) {
            printf("PID: %d, PPID: %d. Exit code: %d.\n", getpid(), getppid(), code);
            exit(code);
        }
    }

    /* Polling part of code */
    int status;
    pid_t res;

    do {
        
        // wait for the last child to terminate
        res = waitpid(pid, &status, WNOHANG);

        if (res == -1) {
            printf("waitpid failed.\n");
            exit(1);
        }
    } while (res == 0);

    printf("Child %d exited, status =%d\n", pid, WEXITSTATUS(status));

    return 0;
}