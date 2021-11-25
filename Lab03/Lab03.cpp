#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
static long num_steps;
double step;
#define PAD 8 
int main(int argc, char* argv[])
{
	int i, nthreads; double pi, sum[128][PAD];
	double start, stop, czas;
	int ile;
	ile = 1;//liczba watkow
	num_steps = 2000000000;
	if (argc >= 2)
	{
		ile = atoi(argv[1]);
	}
	step = 1.0 / (double)num_steps;
	omp_set_num_threads(ile);
	start = omp_get_wtime();
#pragma omp parallel
	{ int i, id, nthrds;
	double x;
	id = omp_get_thread_num();
	nthrds = omp_get_num_threads();
	if (id == 0) nthreads = nthrds;
	for (i = id, sum[id][0] = 0.0; i < num_steps; i = i + nthrds) {
		x = (i + 0.5) * step;
		sum[id][0] += 4.0 / (1.0 + x * x);
	}
	}
	for (i = 0, pi = 0.0; i < nthreads; i++)pi += sum[i][0] * step;
	stop = omp_get_wtime();
	czas = stop - start;
	printf("\n Watkow  %d     ", ile);
	printf(" pi  %f    ", pi);
	printf(" czas  %f ", czas);
}