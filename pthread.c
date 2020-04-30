#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 4
#define LEN 20
#define MAX 10

struct thread_data {
    long thread_id;
    long rand;
};

struct thread_data thread_data_array[NUM_THREADS];

void *multRand (void * args) {
    struct thread_data * num;
    num = (struct thread_data *) args;

    long tid, rd;
    tid = num-> thread_id;
    rd = num-> rand;

    printf("THREAD #ld\t|\trandomic = %ld\t|\tresult = %ld\n", tid, rd, tid*rd);

    pthread_exit(NULL);
}

int main (int argc, char * argv[]) {
    pthread_t threads[NUM_THREADS];
    srand (time(NULL));

    int rc;
    long t;
    for (t = 0; t < NUM_THREADS; t++) {
      thread_data_array[t].thread_id = t;
      thread_data_array[t].rand = rand() % MAX+1;
      rc = pthread_create(&threads[t], NULL, multRand, (* void) &thread_data_array[t]);
      if(rc) {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
      }
    }

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
        }
    }
  }
}
