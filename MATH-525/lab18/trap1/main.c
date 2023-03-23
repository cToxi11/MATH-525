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
    void usage ( const char* prog_name );
    double CompTrap ( const double a, const double b, const int N);

    if (argc != 4) { usage (argv [0]); }
    const int thread_count = strtol (argv [1] , NULL , 10);
    const int N = strtol (argv [2] , NULL , 10);
    const int K = strtol (argv [2] , NULL , 10);
    if ( thread_count <1 || N <1 || N % thread_count != 0)
    { usage (argv [0]); }


    srand (time(NULL));
    const double time1 = omp_get_wtime ();


    vector W = new_vector(N);
    double value = 0.0;
    double W_norm = 0.0;

    # pragma omp parallel for num_threads (thread_count)
    for (int i=1; i <=N; i++)
    {
        vget(W, i) = ComW(N, K, &value);
        W_norm += fabs(get(W, i));
    }

    const double time2 = omp_get_wtime ();
    const double clock_time = time2 - time1 ;

    printf(" With %i threads , clock_time = %11.5e (sec)\n", thread_count, clock_time);
    delete_vector(&W);

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

double CompW(const int N, const int K, double* value)
{
    double func(const double x);
    

    return h*T;
}

double func(const double x)
{
	return(1.0 + exp(x));
}