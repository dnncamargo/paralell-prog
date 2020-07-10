#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "main.h"

int main(int argc, char * argv[]) {
    if( argc == 4) {

        //printf ("%d", isgreaterthan0( strtol ( argv[1], NULL, 10 ) ) );

        //printf ("%d\n", isnotnull (argv[1]));

        double a = strtod (argv[1], NULL);
        double b = strtod (argv[2], NULL);
        double c = strtod (argv[3], NULL);
        printf("%f\n", fquad(a, b, c));
        return 0; 
    } else {
        perror("Too few arguments for mark calculator");
        return -1;
    }
}