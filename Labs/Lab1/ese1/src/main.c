/**
 * Utilizzando solamente le system call open e read, e la funzione printf, realizzare un
 * programma che simuli il comportamento del comando cat. Utilizzo: my_cat <file1> ... <filen>
 */

/* Custom */
#include "errExit.h"

/* Standard */
#include <stdio.h>
#include <stdlib.h>

/* Open */
#include <sys/stat.h>
#include <fcntl.h>

/* Read */
#include <unistd.h>

#define BUFFER_SZ 100
char buffer[BUFFER_SZ+1];

int main(int argc, char *argv[]) {
    // For each file provided as input argument
    for (int i = 1; i < argc; i++) {
        int fileDesc = open(argv[i], O_RDONLY);
        if (fileDesc == -1) {
            printf("File %s does not exist\n", argv[i]);
            continue;
        }

        ssize_t bufReader = 0;
        do {
            // read the file in chunks
            bufReader = read(fileDesc, buffer, BUFFER_SZ);
            if (bufReader > 0) { 
                // add the string terminator at the end before print
                buffer[bufReader] = '\0';
                printf("%s", buffer);
            }
        } while (bufReader > 0);

        // close the file descriptor
        close(fileDesc);
    }    
    
    return 0;
}
