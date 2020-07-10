#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int nthreads, tid, value;

	//Definição da diretiva do OpenMP
	//Diretiva OpenMP que determina o processamento paralelo padrão entre todas as threads criadas, com variável compartilhada value e as variáveis privadas nthreads e tid 
	#pragma omp parallel shared (value) private (nthreads, tid) num_threads(8)
	{

		// Cada thread obtém o seu identificador
		tid = omp_get_thread_num ();
		printf ("Hello from thread %d\n", tid);
		if (tid == 1) {
			value = 2;
			printf ("Process %d changed value to %d\n", tid, value);
		}

		if (tid == 0 ) {
			nthreads = omp_get_num_threads ();
			printf ("I am thread %d and we have %d threads\n", tid, nthreads);
			value = 1;
			printf ("Process %d changed value to %d\n", tid, value);
		}
		// system ("stress -c 1");
	}
	// Fim da diretiva pragma e do processamento paralelo

	return 0;
}
















