#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void *printhello (void *);

/* Programa cria threads e imprime o número de cada uma */

int main (int argc, char * argv[]) {

    pthread_t threads[NUM_THREADS];  // vetor de threads
    int rc; // return code
    long t; // id da thread

    for (t = 0; t < NUM_THREADS; t++) {

      printf("In main: creating thread %ld\n", t);

      rc = pthread_create(&threads[t], NULL, printhello, (void *) t); // cast para void do id da thread
      
      if(rc) {
        printf("ERROR: return code from pthread_create() is %d\n", rc);
        exit(-1);
      }
    }
    pthread_exit(NULL);
}

void *printhello (void * threadid) {
  long tid; // declaração da variável
  tid = (long) threadid; // cast e inicialização;
  printf("Hello World! It's me, thread #%ld!\n", tid);
  pthread_exit(NULL);
}
