# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>
# ifdef _OPENMP
    # include <omp.h>
# endif


int main(int argc , char* argv [])
{
    void usage(const char* prog_name);
    void Matrix_W(const int N, const int K, double *norm);

    if (argc != 4) { usage (argv [0]); }
    const int thread_count = strtol (argv [1] , NULL , 10);
    const int N = strtol (argv [2] , NULL , 10);
    const int K = strtol (argv [3] , NULL , 10);
    if ( thread_count <1 || N <1 || N % thread_count != 0)
    { usage (argv [0]); }

    double norm = 0.0;
    const double time1 = omp_get_wtime();
    

//#   pragma omp parallel for num_threads(thread_count)
    Matrix_W(N, K, &norm);
    const double time2 = omp_get_wtime();
    const double clock_time = time2 - time1;

    printf(" With %i threads , clock_time = %11.5e (sec), the L-1 norm is %f\n", thread_count, clock_time, norm);

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

void Matrix_W(const int N, const int K, double *norm)
{
#   ifdef _OPENMP
    const int my_rank = omp_get_thread_num();
    const int thread_count = omp_get_num_threads();
#   else
    const int my_rank = 0;
    const int thread_count = 1;
#   endif
    int local_n = N / thread_count;
    double i_begin = my_rank * local_n + 1;
    double i_end = (my_rank + 1) * local_n;

    double W_i;
    for (double i=i_begin; i<=i_end; i++)
    {
        W_i = 0.0;
        for (double j=1.0; i<=K; j++)
        {
            W_i += 1.0/(i + j - 1)/j;
        }
#       pragma omp critical
        *norm += fabs(W_i);
    }

}
