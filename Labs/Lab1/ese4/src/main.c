/* Realizzare un programma che simuli il comportamento del comando cp, con i seguenti scenari
 * di utilizzo: 
 *  1. mcp <source> <destination>: il programma copia il contenuto del file <source> in un
 *  nuovo file di nome <destination>. Se il file <destination> gia' esiste, il programma
 *  stampa a video la stringa: "il file <destination> gia' esiste!"
 *  2. mcp -s <source> <destination>: il programma copia il contenuto del file <source>
 *  in un nuovo file di nome <destination>. Se il file <destination> gia' esiste, il 
 *  programma sovrascrive il contenuto del file <destination> con il contenuto del file
 *  <source>.
 *  3. mcp -a <source> <destination>: Il programma aggiunge in fondo al file <destination>
 *  il contenuto del file <source>. Se il flie <destination> non esiste, il programma stampa
 *  a video la stringa: "Il file <destination> non esiste!" 
 */

#include "errExit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

/* ==== DEFINE CONSTANT(s) ==== */

#define BUFF_SZ 100

/* ==== ACCESSORY FUNCTION(s) ==== */
void printUsage(char * _argv[]) 
{
    printf("Usage: %s [option] <sourceFile> <destinationFile>\n", _argv[0]);
    printf("option:\n");
    printf("-a: append\t<sourceFile> to <destinationFile>\n");
    printf("-s: overwrite\t<destinationFile> with <sourceFile>\n");
}


int main(int argc, char *argv[]) 
{
    char buffer[BUFF_SZ + 1];

    // check command line arguments
    if (argc != 3 && argc != 4) {
        printUsage(argv);
        return 1;
    }

    // flag variable, wich is used to store either option -a, or -s.
    char *flag = NULL;
    // pathnames
    char *fileSource, *fileDestination;

    // if argc is 4, a flag (-a, -s) were passed.
    if (argc == 4) {
        flag = argv[1];
        fileSource = argv[2];
        fileDestination = argv[3];
    } else {
        fileSource = argv[1];
        fileDestination = argv[2];
    }
    
    // open the source file only for reading
    int fdSrc = open(fileSource, O_RDONLY);
    if (fdSrc == -1) 
        errExit("open failed");
    
    int fdDst = -1;
    // if flag is NULL, then no flag was provided as input argument
    if (flag == NULL) {
        // check if destination file already exists
        if (access(fileDestination, F_OK) == 0) 
        {
            printf("ERROR: File %s already exists\n", fileDestination);
            return 1;
        }
        
        // create and open the destination file for only writing
        fdDst = open(fileDestination, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    } else if (strcmp(flag, "-s") == 0) {
        // Open new or existing file for only writing. If the file destination file
        // already exists, truncate it to zero bytes.
        fdDst = open(fileDestination, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, S_IRUSR | S_IWUSR);
    } else if (strcmp(flag, "-a") == 0) {
        // check if <fileSource> and <fileDestination> are the same
        if (strcmp(fileSource, fileDestination) == 0) 
        {
            printf("ERROR: <source file> and <destination file> must be different\n");
            return 1;
        }
        // check if the destination file exists and can be written
        if (access(fileDestination, F_OK | W_OK) != 0) 
        {
            printf("ERROR: %s doesn't exists or can't be written", fileDestination);
            return 1;
        }
        // open the destination file in write only mode and append the source file content.
        fdDst = open(fileDestination, O_WRONLY | O_APPEND);
    } else {
        // wrong flag is given
        printf("The flag %s is not recognized\n", flag);
        printUsage(argv);
        return 1;    
    } 

    // check if the open syscall went wrong
    if (fdDst == -1) 
    {
        errExit("open failed");
    }

    ssize_t bytesRead;
    do {
        bytesRead = read(fdSrc, buffer, sizeof(buffer));
        // check if read syscall went wrong
        if (bytesRead == -1) 
        {
            errExit("read failed");
        }

        // write the content in the destination file
        if (bytesRead > 0 && write(fdDst, buffer, bytesRead) != bytesRead) 
        {
            errExit("write failed");
        }
    } while (bytesRead > 0);
    
    // close all file descriptors before ending the program 
    if (close(fdSrc) == -1 || close(fdDst) == -1)
        errExit("close failed");
    
    return 0;
}
