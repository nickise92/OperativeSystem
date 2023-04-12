
/**
 * Scrivere un programma che legge della riga di comando un comando di sistema X e
 * i suoi argomenti. Il programma crea un processo figlio, il quale, utilizzando la 
 * system call exec, esegue X redirezionando il suo standard output ed error su un 
 * file di testo. Il processo parent attende la terminazione del processo figlio, 
 * stampa a video il codice di terminazione, ed infine termina.
 */
#include "errExit.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    // Check command line input arguments
    if (argc <= 1) {
        printf("Usage: %s cmd [arguments]\n", argv[0]);
        return 0;
    }

    switch (fork()) {
        case -1: {
            errExit("fork");
        }
        case 0: {    /* child process */
           
            // Close standard output and error
            close(STDOUT_FILENO);   // close file descriptor 1
            close(STDERR_FILENO);   // close file descriptor 2

            /* create a new file. The value returned by open will be 1 as it is
             * the lowest available */
            char * filename = "file_output.txt";
            int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_RDONLY, S_IRUSR | S_IWUSR);

            if (fd == -1) {
                errExit("open");
            }
            /* clone the file descriptor 1. The value returned by dub will be 2
            * as it is lowst available index */
            dup(fd);

            // both file descriptors 1 and 2 are pointing at the created file now.

            // replace the current process image with a new process image
            execvp(argv[1], &argv[1]);
            errExit("execvp failed");
        }
        default: {
            int status;
            // wait the termination of the child process
            if (wait(&status) == -1) {
                errExit("wait");
            }

            printf("Command %s exited with status %d\n", argv[1], WEXITSTATUS(status));
        }
    }

    return 0;
}