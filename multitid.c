#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define MAX 10

void * multrand (void *);

/* Criar um programa em C com 4 threads no qual cada uma delas multiplica o seu próprio thread_id por um valor
randômico entre 1 e 10, gerado pela função principal. Após multiplicar, cada thread deve exibir o valor randômico e o
produto. */

typedef struct thread_data {
    long thread_id;
    long rand;
} tdata; // definição do struct (argumentos da thread)

tdata tdataarray[NUM_THREADS]; // vetor de structs

int main() {

    pthread_t vthreads[NUM_THREADS]; // vetor de threads
    int rc; // return code
    long t; // id da thread
    srand (time(NULL));

    for (t = 0; t < NUM_THREADS; t++) {

        tdataarray[t].thread_id = t;
        tdataarray[t].rand = rand() % MAX + 1;

        rc = pthread_create(&vthreads[t], NULL, multrand, (void*) &tdataarray[t]); // cast para void do endereço do vetor de structs

        if(rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}

void * multrand (void * tid) {
    tdata * std; // declaração da variável struct
    std = (tdata *) tid; // cast e inicialização;

    long t, r;
    t = std-> thread_id;
    r = std-> rand;

    printf("THREAD %ld:: Randomic: %ld\n", t, r);
}
