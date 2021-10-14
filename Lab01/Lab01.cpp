#include <iostream>
#include <omp.h>

int main(int argc, char* argv[])
{
	printf("Hello\n");
	int threads = 1;
	if (argc >= 2)
	{
		threads = atoi(argv[1]);
	}
	omp_set_num_threads(threads);
	double start = 0, stop = 0;
	int ile = 100000;
	double s1 = 0;
	start = omp_get_wtime();
	double d = 1.0 / (double)ile;
	#pragma omp parallel shared(s1,ile)
	{
		#pragma omp for collapse(2) reduction(+:s1)
		for (int i = 0; i < ile; i++)
		{
			for (int j = 0; j < ile; j++)
			{
				double x = d * i;
				double y = d * j;
				double r2 = x * x + y * y;
				if (r2 < 1)s1 = s1 + 1;
			}
		}
	}
	double s = (double)ile * (double)ile;
	double pi = s1 / s * 4;
	printf("\ns1 %15.12f\n", s1);
	printf("\ns %15.12f\n", s);
	printf("\n pole %15.12f\n", pi);
	stop = omp_get_wtime();
	double czas = stop - start;
	printf("\n czas %15.5f s \n", czas);
}
