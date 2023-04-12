
/**
 * Scrivere un programma che legge da riga di comando un intero positivo N.
 * Il programma successivamente crea N processi figlio. Ogni processo figlio, stampa a
 * video il suo PID, il PID del suo processo padre, ed infine termina con un codice di
 * terminazione (un numero casuale tre 0 e 255). Dopo avere creato N processi figlio, il
 * programma attende la terminazione di ogni processo figlio. Ogni qualvolta un 
 * processo figlio termina, il programma stampa a video il codice di terminazione del figlio.
 */
#include "errExit.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    // check command line input arguments
    if (argc != 2) {
        printf("Usage: %s numSubProcess\n", argv[0]); // argv[0] contiene il nome del programma stesso
        return(0);
    }
    
    int n = atoi(argv[1]);
    if (n < 0) {
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

    int status = 0;
    // get termination status of each created subprocess.
    while((pid = wait(&status)) != -1) {
        printf("Child %d exited, status=%d\n", pid, WEXITSTATUS(status));
    }

    return 0;
}