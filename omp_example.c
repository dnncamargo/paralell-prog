#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
	int nthreads, tid, value;

  	/* Divide em um conjunto de threads, cada uma com suas próprias variáveis */
  	#pragma omp parallel shared (value) private(nthreads, tid)
	{

  		/* Obtém o id da thread */
  		tid = omp_get_thread_num(); //cada thread obtém o seu próprio id
  		printf("Hello World from thread = %d\n", tid);
		system ("stress -c 1");

  		/* Restrição de execução para uma thread específica */
  		if (tid == 0) {
    			nthreads = omp_get_num_threads(); //obtém-se o total de threads
    			printf("Number of threads = %d\n", nthreads);
  		}

  	}  /* Todas as threads se juntam ao processo principal e encerram */

}


