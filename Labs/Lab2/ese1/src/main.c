/* Utilizzando la variabile environ, scriveere un programma che legge lo username
 * (variabile USER) e la home (variabile HOME) dell'utente utilizzatore.
 * Il programma confronta il path della sua attuale direcotry di lavoro con la home directory
 * dell'utente. Se la directory di lavoro non e' una sotto direcotry della home direcotry 
 * dell'utente, il programma imposta la home direcotry dell'utente come sua directory di lavoro, 
 * crea un file di testo vuoto e stampa a video: "Caro USER, sono dentro la tua home!", dove 
 * USER e' l'username dell'utente.
 */

#include "errExit.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SZ 100

int main(int argc, char *argv[]) {

    char *username = getenv("USER");
    if (username == NULL)
    {
        username = "unknown";
    }

    char *homeDir = getenv("HOME");
    if (homeDir == NULL)
    {
        printf("Unknown home directory");
        exit(0);
    }

    char buffer[BUFFER_SZ];
    if (getcwd(buffer, sizeof(buffer)) == NULL)
    {
        errExit("getcwd failed\n");
    }

    int subDir = strncmp(buffer, homeDir, strlen(homeDir));

    if (subDir == 0)
    {
        printf("Dear %s, I'm already in the right directory!\n", username);
    }
    else
    {
        if (chdir(homeDir) == -1) {
            //errExit("chdir failed");
            perror("chdir");
            return -1;
        }
        // open the file
        int fd = open("empty_file.txt", O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd == -1)
        {
            errExit("open failed");
        }

        // Creating the message for write syscall
        char messageBuffer[BUFFER_SZ] = "Dear ";
        char *msgPtr;
        msgPtr = strcat(messageBuffer, username);
        msgPtr = strcat(messageBuffer, ", I'm in your home directory!");

        if (0 > write(fd, messageBuffer, sizeof(messageBuffer)))
        {
            errExit("write failed");
        }


        // close file descriptor
        if (close(fd) == -1){
            errExit("close failed");
        }

    }

    return 0;
}