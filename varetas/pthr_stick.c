#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

/**
    Trabalho de Programacao Paralela
    @file pthr_stick.c
    @author Daniel Neves Camargo - 20161107403
    @version 1.1 23/06/2020
*/

/* structure of a thread */
struct thread_data {
    long thread_id;
    long len;
};

/* global mutex */
pthread_mutex_t mshar;
int * vshar;
long t;

/* function statement */
void * getstick (void *);

int main(int argc, char *argv[]) {

    /* getting number of threads */
    if(argc != 2) {
        printf("Specify the number of threads in the program call\n");
        return -1;
    }
    char *ptr;
    long num_threads;
    num_threads = strtol(argv[1], &ptr, 10);

    /* generating random */
    srand (time(NULL));
    vshar = (int *) malloc (num_threads * sizeof(int));
    for (t = 0; t < num_threads; t++)
        vshar[t] = rand() % MAX + 1;

    /* threads */
    pthread_t vthreads[num_threads]; // array de threads
    struct thread_data thread_data_array[num_threads]; // array of struct

    int rc;

    for (t = 0; t < num_threads; t++) {

        pthread_mutex_lock(&mshar); // start critical session
        thread_data_array[t].thread_id = t;
        pthread_mutex_unlock(&mshar); // end critical session

        /* creating threads*/
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&vthreads[t], NULL, getstick, (void *) &thread_data_array[t]);

        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }

    }

    /* join threads */
    for (t = 0; t < num_threads; t++)
        pthread_join (vthreads[t], NULL);

    /* showing results */
    int winnerthread = thread_data_array[0].thread_id;
    int biggeststick = thread_data_array[0].len;

    for(t = 1; t < num_threads; t++) {
        if(thread_data_array[t].len > biggeststick) {
            biggeststick = thread_data_array[t].len;
            winnerthread = thread_data_array[t].thread_id;
        }
    }
    printf("Showing result for %d players: The player %d has the biggest stick with %d!\n", num_threads, winnerthread, biggeststick);

    free(vshar);
    pthread_mutex_destroy (&mshar); // destruição do mutex
    pthread_exit(NULL);
}


void * getstick(void *thread) {

    /* cast value */
    struct thread_data * ipt; // individual thread
    ipt = (struct thread_data *) thread;

    long tid, rnd;
    tid = ipt-> thread_id; // index array
    pthread_mutex_lock(&mshar); // start critical session

    rnd = vshar[tid];
    ipt-> len = rnd;
    vshar[tid] = -1;

    pthread_mutex_unlock(&mshar); // end critical session
    //printf("Hi, I'm %ld and my number is %ld\n", tid, rnd);
    pthread_exit(NULL);
}

/* O jogo de sorteio com palitos de madeira consiste de uma determinada quantidade N de
jogadores e uma quantidade N de palitos de madeira. Cada jogador, um de cada vez, deve retirar um
palito do conjunto, sem saber o seu tamanho, até que todos possuam exatamente um palito. Uma
vez que todos os palitos forem retirados do conjunto, os jogadores tornam públicos os seus palitos.
O árbitro então decide como vencedor do sorteio aquele que tiver o palito de maior valor.
Elabore um programa em C e que utilize Pthreads para simular o jogo de sorteio com
palitos. O programa deve considerar os N jogadores como sendo um conjunto de N threads. Os
palitos devem ser representados por elementos de um vetor de N posições (N palitos) que será
compartilhado por todas as threads, cujos valores devem ser positivos e diferentes de zero e
menores do que 100. Os valores dos palitos devem ser gerados aleatoriamente pelo processso
principal.
A retirada dos palitos deve ser controlada por meio de exclusão mútua (variável mutex), de
modo que apenas uma thread por vez deve ter acesso ao vetor compartilhado.
Quando um palito é retirado do vetor, o valor correspondente àquela posição passa a ser
igual a -1, de modo a identificar que ele não pode ser mais utilizado. A thread que detém a posse do
mutex deve continuar procurando por um palito válido até encontrá-lo.
Uma vez que todas as threads possuírem um palito, elas devem enviar seus valores para o
processo principal (árbrito), que será responsável por verificar qual o maior palito e por declarar a
thread vencedora.
Para garantir uma justiça maior no sorteio, as threads só podem iniciar o sorteio uma vez que
todas elas tenham sido criadas.*/
