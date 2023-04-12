/* Utilizzando solamente le system call open, read, lseek, e write, realizzare un
 * programma che simuli il comportamento del comando tac. Al contrario di cat, il
 * comando tac stampa il contenuto di un file al contrario (dall’ultimo carattere al
 * primo) Utilizzo: my_tac <file1> ... <filen>
 */

#include "errExit.h"
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    
    char buff;

    // Check command line arguments
    if (argc < 2) 
    {
        printf("Usage: ./mtac <file1> <file2> ... <filen>\nNo enough argument(s) given\n");
        return 0;
    }

    // open file
    for (int i=1; i < argc; i++) 
    {
        int fd = open(argv[i], O_RDONLY);
        
        if (fd == -1) 
        {
            printf("File %s does not exist\n", argv[i]);
            continue;
        }
        
        // find end of file with lseek
        off_t currOffset = lseek(fd, -1, SEEK_END);
        
        while (currOffset >= 0) 
        {
            // read a char from the file
            ssize_t chRead = read(fd, &buff, sizeof(char));

            // write on the standard output
            if (chRead == sizeof(char)) 
            {
                if (write(STDOUT_FILENO, &buff, sizeof(char)) != sizeof(char))
                {
                        errExit("write failed");
                }
                // Update offset location
                // -2 because every time we read from file the
                // cursor goes forward by 1, we need to go back 
                // by 2 to read the previous character.
                currOffset = lseek(fd, -2, SEEK_CUR);
            }
        }   
        // close file descriptor
        close(fd);
        // pring a new line before starting the next file
        buff = '\n';
        int chWr = write(STDOUT_FILENO, &buff, sizeof(char));
        if (chWr == -1) 
        {
            errExit("write failed");
        }
    }   

    return 0;
}
