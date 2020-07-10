#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 6

void * varmutex (void *);

/* Uso de mutex para bloqueio de variável compartilhada */

pthread_t threads[NUM_THREADS]; // vetor de threads
pthread_mutex_t mutexcomp; // declaração do mutex
long varshar; // variável compartilhada

int main(int argc, char * argv[]) {
    int rc;
    long t;

    pthread_mutex_init (&mutexcomp, NULL); // inicialização do mutex

    for (t = 0; t < NUM_THREADS; t++) {
        printf("######\tPrincipal iniciando MUTEX e modificando váriavel compartilhada\t######\n");

        pthread_mutex_lock(&mutexcomp); // inicio de seção crítica
        varshar = 1;
        varshar = -1 * varshar;
        printf("\t#\tThread %ld computou o valor %ld para varshar\t\t#\n", t, varshar);
        pthread_mutex_unlock(&mutexcomp); // fim de seção crítica

        printf("######\tThread %ld finalizou MUTEX e modificou variável compartilhada\t######\n", t);

        rc = pthread_create(&threads[t], NULL, varmutex, (void *) t); // criação das threads

        if(rc) {
            printf("ERROR, return code from pthread_create is %d\n", rc);
            exit(-1);
        }
    }
    pthread_mutex_destroy (&mutexcomp); // destruição do mutex
    pthread_exit(NULL);
}

void * varmutex (void * t) {
    long tid = (long) t; // declaração e inicialização de variável parâmetro
    printf("######\tThread %ld iniciando MUTEX e modificando variável compartilhada\t######\n", tid);

    pthread_mutex_lock (&mutexcomp); // Inicio da seção crítica
    varshar = 1;
    varshar = tid * varshar;
    printf("\t#\tThread %ld computou o valor %ld para varshar\t\t#\n", tid, varshar);
    pthread_mutex_unlock(&mutexcomp); // Fim da seção crítica

    printf("######\tThread %ld finalizando MUTEX e modificando variável compartilhada\t######\n", tid);
    pthread_exit(NULL);
}
