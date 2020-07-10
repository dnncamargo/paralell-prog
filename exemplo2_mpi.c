#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv[]) {
	int size, rank, dest, source, value;
	MPI_Status status;

	MPI_Init (&argc, &argv);

	MPI_Comm_size (MPI_COMM_WORLD, &size);

	MPI_Comm_rank (MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		value = 100;
		for (dest = 1; dest < size; dest++) {
			printf ("## Mestre enviou %d p/ processo %d ##\n", value, dest);
			MPI_Send (&value, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
		}

		for (source = 1; source < size; source++) {
			MPI_Recv (&value, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status);
			printf ("## Mestre recebeu %d do processo %d ##\n", value, source);
		}
	}
	else {
		source = 0;
		dest = 0;
		MPI_Recv (&value, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status);
		printf ("## Processo %d recebeu valor %d ##\n", rank, value);
		value += rank;
		printf ("## Processo %d enviou %d p/ o mestre ##\n", rank, value);
		MPI_Send (&value, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize ();

	return 0;
}












