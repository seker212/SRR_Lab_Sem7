#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
	long num_steps;
	double step, start, stop, pi_part, pi, sum, x;
	int i, nthreads, myid, numprocs, my_first, my_last;
	num_steps = 2000000000;
	step = 1.0 / (double)num_steps;
	sum = 0.0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Barrier(MPI_COMM_WORLD);
	if (myid == 0) start = MPI_Wtime();
	my_first = myid * (num_steps / numprocs);
	my_last = (myid + 1) * (num_steps / numprocs);
	for (i = my_first; i < my_last; i++)
	{
		x = (i + 0.5) * step;
		sum += 4.0 / (1.0 + x * x);
	}
	pi_part = sum * step;
	MPI_Reduce(&pi_part, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if (myid == 0) {
		stop = MPI_Wtime();
		printf("czas %f\n", stop - start);
		printf("pi  %f    ", pi);
	}
	MPI_Finalize();
}