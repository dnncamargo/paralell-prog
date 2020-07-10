#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void *printmessage (void *);

/* Programa cria threads para exibir a mensagem sendo enviada via struct */

struct thread_data {
  int thread_id;
  char * message;
};

struct thread_data thread_data_array[NUM_THREADS];

int main (int argc, char * argv[]) {

    pthread_t threads[NUM_THREADS]; // vetor de threads
    int rc; // return code
    long t; // id da thread

    for (t = 0; t < NUM_THREADS; t++) {

      printf("In main: creating thread %ld\n", t);

      thread_data_array[t].thread_id = t;
      thread_data_array[t].message = "Hello World! It's me, thread #";

      rc = pthread_create( &threads[t], NULL, printmessage, (void*) &thread_data_array[t]); // cast para void do endereço do vetor de structs
      if(rc) {
        printf("ERROR: return code from pthread_create() is %d\n", rc);
        exit(-1);
      }
    }
    pthread_exit(NULL);
}

void *printmessage (void * threadparam) {
    struct thread_data * tdata; // declaração da váriável
    tdata = ( struct thread_data * ) threadparam; // cast e inicialização

    int taskid = tdata-> thread_id;
    char * hello_msg = tdata-> message;
    printf("%s%d\n", hello_msg, taskid);
    pthread_exit(NULL);
}
