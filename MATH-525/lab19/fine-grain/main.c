# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>
# ifdef _OPENMP
    # include <omp.h>
# endif
#include "matrix.h"

int main(int argc , char* argv [])
{
    void usage(const char* prog_name);
    void Matrix_W(const int N, const int K, double *norm);

    if (argc != 3) { usage (argv[0]); }
    const int thread_count = strtol (argv[1] , NULL , 10);
    const int N = strtol (argv[2] , NULL , 10);
    if ( thread_count <1 || N <1 || N % thread_count != 0)
    { usage (argv [0]); }
    
    srand ( time(NULL) );

    vector x1 = new_vector(N);
    for (int i=1; i <=N; i++)
    { vget(x1,i) = -1/i; }

    //fine-grain approach
    
    const double finegrain_time1 = omp_get_wtime();
    double norm = 0.0;
    # pragma omp parallel num_threads (thread_count)
    {
        # pragma omp for reduction (+: norm)
        for (int i=1; i <=N; i++)
        { norm += vget(x1,i) * vget(x1,i); }

        # pragma omp barrier // not needed ( implicit )
        norm = sqrt(norm);
        # pragma omp for
        for (int i=1; i <=N; i++)
        { vget(x1,i) = vget(x1,i)/norm; }
    }


    const double finegrain_time2 = omp_get_wtime();
    const double finegrain_clock_time = finegrain_time2 - finegrain_time1;

    printf(" With %i threads , fine-graind approach clock_time = %11.5e (sec), the L-2 norm is %f\n", thread_count, finegrain_clock_time, norm);

    vector x2 = new_vector(N);
    for (int i=1; i <=N; i++)
    { vget(x2,i) = -1/i; }

    //coarse-grain approach

    const double coarsegrain_time1 = omp_get_wtime();
    norm = 0.0;

    # pragma omp parallel num_threads (thread_count)
    {
        const int my_rank = omp_get_thread_num ();

        const int N_per_thread = N/ thread_count ;
        const int istart = my_rank * N_per_thread + 1;
        const int iend = ( my_rank +1) *( N_per_thread );

        double norm_thread = 0.0;
        for (int i= istart ; i <= iend; i++)
        { norm_thread += fabs(vget(x2,i)) * fabs(vget(x2,i)); }
        
        # pragma omp critical
        norm += norm_thread ;

        # pragma omp barrier // needed here
        norm = sqrt(norm);

        for (int i= istart ; i <= iend; i++)
        { vget(x2,i) = vget(x2,i)/norm; }
    }

    const double coarsegrain_time2 = omp_get_wtime();
    const double coarsegrain_clock_time = coarsegrain_time2 - coarsegrain_time1;

    printf(" With %i threads , coarse-grain approach clock_time = %11.5e (sec), the L-2 norm is %f\n", thread_count, coarsegrain_clock_time, norm);


    return 0;
}

void usage(const char * prog_name)
{
    fprintf (stderr, "usage : %s <num_intervals >\n", prog_name);
    fprintf (stderr, "num_threads should be positive \n");
    fprintf (stderr, "N should be positive \n");
    exit (1);
}























