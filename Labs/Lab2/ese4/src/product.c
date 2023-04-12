#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    /* check command line input args 2 integer 
     * expected in argv[1] and argv[2]. */
    if (argc != 3) {
        printf("Usage: %s num1 num2", argv[0]);
        return 0;
    }

    // take the two number and convert to int
    int firstNum = atoi(argv[1]);
    int secondNum = atoi(argv[2]);

    printf("The product between %d and %d is: %d", 
        firstNum, secondNum, firstNum*secondNum);

    return 0;
}