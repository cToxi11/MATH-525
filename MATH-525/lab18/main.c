# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "matrix.h"
# include <math.h>
# ifdef _OPENMP
    # include <omp.h>
# endif


int main(int argc , char* argv [])
{
    void usage(const char* prog_name);
    double CompW(const int i, const int K, const vector* V);

    if (argc != 4) { usage (argv [0]); }
    const int thread_count = strtol (argv [1] , NULL , 10);
    const int N = strtol (argv [2] , NULL , 10);
    const int K = strtol (argv [2] , NULL , 10);
    if ( thread_count <1 || N <1 || N % thread_count != 0)
    { usage (argv [0]); }


    srand (time(NULL));
    const double time1 = omp_get_wtime ();


    vector W = new_vector(N);
    vector V = new_vector(N);
    double W_norm = 0.0;

    for (int i=1; i<=K; i++) {vget(V, i) = 1/i;}

    # pragma omp parallel for num_threads (thread_count)
    
    for (int i=1; i <=N; i++)
    {
        vget(W, i) = CompW(i, K, &V);
        W_norm += fabs(vget(W, i));
    }

    const double time2 = omp_get_wtime ();
    const double clock_time = time2 - time1 ;

    printf(" With %i threads , clock_time = %11.5e (sec)\n", thread_count, clock_time);
    delete_vector(&W);
    delete_vector(&V);

    return 0;
}

void usage(const char * prog_name)
{
    fprintf (stderr, "usage : %s <num_intervals >\n", prog_name );
    fprintf (stderr, "num_threads should be positive \n");
    fprintf (stderr, "Row number should be positive \n");
    fprintf (stderr, "Column number should be positive \n");
    exit (1);
}

double CompW(const int m, const int K, const vector* V)
{
    double value = 0.0;
    for (int j=1; j <=K; j++)
    {
        value += vgetp(V, j) / (m + j - 1);
    }
    
    return value;

 
}


