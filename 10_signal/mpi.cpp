#include "mpi.h"

int main(int argc, char * argv[]) {
	int a[60], rank, size;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		MPI_Send(a, 20, MPI_INT, 1, 99, MPI_COMM_WORLD);
	}
	if (rank == 1) {
		MPI_Recv(a, 20, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
	}
	MPI_Finalize();
}
