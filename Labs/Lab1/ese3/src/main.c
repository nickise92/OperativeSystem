/* Realizzare un programma che sfruttando le system call per la gestione dei file
 * esegua un search_replace di un carattere all’interno di un file.
 * search_replace <source file> <destination file> <char search> <char replace>
 * Il programma copia il contenuto del file <source file> in un nuovo file di nome
 * <destination file>. Dovrà sostituire tutte le occorrenze di <char search> con <char replace>
 */

#include "errExit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{

    // vars
    char *charSearch, *charReplace;
    char *fileSource, *fileDestination;
        
    // check command line arguments 
    if (argc != 5) 
    {
        printf("ERROR: Not enough argument(s).\nSearch and Replace Usage: %s <file_source> <file_destination> <char_to_search> <char_to_replace>.\n", argv[0]);      
        return 1;
    } else {
        fileSource = argv[1];
        fileDestination = argv[2];
        charSearch = argv[3];
        charReplace = argv[4];
    }
        
    // open source file in read only mode
    int sourceFd = open(fileSource, O_RDONLY);
    if (sourceFd == -1)
    {
        printf("ERROR: Open failed.\n%s does not exist.\n", argv[1]);
        errExit("source open failed");
    }
    
    int destinationFd = -1;
    // check if the destination file already exists
    if (access(fileDestination, F_OK) == 0) 
    {
        printf("ERROR: %s already exist\n", fileDestination);
        return 1;
    }

    // create and open the destination file 
    destinationFd = open(fileDestination, O_WRONLY | O_CREAT | O_EXCL, S_IWUSR | S_IRUSR);
    if (destinationFd == -1) 
    {
        errExit("open failed");
    }
    
    // read one char from source file
    char buffer;
    ssize_t chRead; 

    do {

        chRead = read(sourceFd, &buffer, sizeof(char));

        // check if read went wrong
        if (chRead == -1) 
        {
            errExit("read failed.");
        }
    
        // check if the character read has to be replaced
        if (buffer == *charSearch) 
        { 
            buffer = *charReplace;
        }
        
        // write the read character
        if (chRead > 0) {
            ssize_t chWrite = write(destinationFd, &buffer, sizeof(char));
            if (chWrite == -1) 
            {
                errExit("Write failed.");
            }
        }
    } while (chRead > 0);
        
    // close file descriptor
    close(sourceFd);
    close(destinationFd);
    return 0;
}

