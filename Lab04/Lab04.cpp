#include <time.h>
#include <mpi.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	int start, stop, czas, ile, i, j, numprocs, myid, my_first, my_last;
	double x, y, d, r2, pi, s, s_part, s1, s1_sum;
	start = clock();
	ile = 100000;
	d = 1.0 / (double)ile;
	s1 = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	my_first = myid * ile / numprocs;
	my_last = (myid + 1) * ile / numprocs;
	for (i = my_first; i < my_last; i++)
	{
		for (j = 0; j < ile; j++)
		{
			x = d * i;
			y = d * j;
			r2 = x * x + y * y;
			if (r2 < 1)s1 = s1 + 1;
		}
	}
	s_part = (double)(my_last - my_first) * (double)ile;
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Reduce(&s1, &s1_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&s_part, &s, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if (myid == 0) {
		pi = s1_sum / s * 4;
		printf("\ns1 %15.12f\n", s1_sum);
		printf("\ns %15.12f\n", s);
		printf("\n pole %15.12f\n", pi);
		stop = clock();// koniec pomiaru czasu
		czas = stop - start;
		printf("\n czas %d  ms \n", czas);
	}
	MPI_Finalize();
}