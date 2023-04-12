
/**
 * Scrivere:
 * a) un programma che legge da riga di comando due interi n, m. Il programma
 * stampa a video la stringa: “Il prodotto di n e m e’: x“, dove x e’ il risultato
 * dell’operazione n*m.
 * b) un secondo programma che genera due numeri casuali. Mediante la system
 * call exec, il programma utilizza il programma descritto nel punto a) per
 * calcolarne il prodotto.
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

#define BUFFER_SZ 20
#define MAX_NUM 100

int main(int argc, char *argv[]) {

    int numX, numY; // random number
    char strX[BUFFER_SZ], strY[BUFFER_SZ];
    // initialize the random seed
    srand(time(0));

    // generate numbers
    numX = (int)(((double)rand() / RAND_MAX) * MAX_NUM);
    numY = (int)(((double)rand() / RAND_MAX) * MAX_NUM); 

    // generate string args
    sprintf(strX, "%d", numX);
    sprintf(strY, "%d", numY);

    // execute the program with generated numbers 
    execl("product", "product", strX, strY, (char *)NULL);
    printf("Exec failed\n");
    
    exit(1);
}