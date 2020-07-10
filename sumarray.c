#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 2
#define LEN 20

/* Crie um programa em C com duas threads. Uma deve invocar uma rotina que calcula o somatório dos valores
contidos em um vetor, enquanto a outra deve encontrar o maior elemento do mesmo vetor. */

void * sumarray (void * vnum) {
    int * v;
    v = (int *) vnum;
    int i, sum = v[0];
    for (i = 1; i < LEN; i++) {
        sum += v[i];
    }
    printf("SUM: %d\n", sum);
    pthread_exit(NULL);
}

void * maxelem (void * vnum) {
    int * v;
    v = (int *) vnum;
    int i, max = v[0];
    for (i = 1; i < LEN; i++) {
        if(v[i] > max) {
            max = v[i];
        }
    }
    printf("MAX: %d\n", max);
    pthread_exit(NULL);
}



int main (int argc, char * argv[]) {
    pthread_t threads[NUM_THREADS];

    int v[LEN] = {40, 38, 36, 32, 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2};
    int rc;
    int t;

    for (t = 0; t < NUM_THREADS; t++) {
        if (t == 0) {
            rc = pthread_create( &threads[t], NULL, sumarray, (void *) &v);
            if (rc){
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(-1);
            }
        } else {
            rc = pthread_create( &threads[t], NULL, maxelem, (void *) &v);
            if (rc){
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(-1);
            }
        }
    }
    pthread_exit(NULL);
}
