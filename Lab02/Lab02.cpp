#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NRA 5000                 /* number of rows in matrix A */
#define NCA 5000                 /* number of columns in matrix A */
#define NCB 5000                  /* number of columns in matrix B */

double	a[NRA][NCA],           /* matrix A to be multiplied */
        b[NCA][NCB],           /* matrix B to be multiplied */
        c[NRA][NCB];           /* result matrix C */

int main(int argc, char* argv[])
{
    double start, stop;
    int	tid, nthreads = 1, i, j, k, chunk;
    int n = NRA, m = NCA, p = NCB;
    double cResult;

    chunk = 10;                    /* set loop iteration chunk size */
    cResult = 0;
    
    if (argc > 1)
        nthreads = atoi(argv[1]);

    if (argc > 4) {
        n = atoi(argv[2]);
        m = atoi(argv[3]);
        p = atoi(argv[4]);
    }

    start = omp_get_wtime();
    omp_set_num_threads(nthreads);
    /*** Spawn a parallel region explicitly scoping all variables ***/
#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Starting matrix multiple example with %d threads\n", nthreads);
        }
        /*** Initialize matrices ***/
#pragma omp for schedule (static, chunk) 
        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                a[i][j] = i + j;
#pragma omp for schedule (static, chunk)
        for (i = 0; i < m; i++)
            for (j = 0; j < p; j++)
                b[i][j] = i * j;
#pragma omp for schedule (static, chunk)
        for (i = 0; i < n; i++)
            for (j = 0; j < p; j++)
                c[i][j] = 0;

        /*** Do matrix multiply sharing iterations on outer loop ***/
        /*** Display who does which iterations for demonstration purposes ***/
#pragma omp for schedule (static, chunk)
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < p; j++)
                for (k = 0; k < m; k++)
                    c[i][j] += a[i][k] * b[k][j];
        }
    }   /*** End of parallel region ***/

#pragma omp for schedule (static, chunk)
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p; j++) cResult += c[i][j];
    }

    stop = omp_get_wtime();// koniec pomiaru czasu

  /*** Print results ***/

    printf("N: %d \n", n);
    printf("M: %d \n", m);
    printf("P: %d \n", p);
    printf("Result: %f \n", cResult);
    printf("Time: %f s\n\n", stop - start);
}