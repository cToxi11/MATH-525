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
    void usage(const char* prog_name );

    if (argc != 3) { usage(argv[0]); }
    const int thread_count = strtol (argv[1] , NULL , 10);
    const int N = strtol (argv[2], NULL , 10);
    if (thread_count <= 0)
    { usage(argv[0]); }

    srand (time(NULL));
    vector v = new_vector (N);
    const double time1 = omp_get_wtime ();

    # pragma omp parallel for num_threads ( thread_count )
    for (int i=1; i <=N; i++)
    {
        const double x = ((double)(i))/((double)(N));
        double sum = 1.0;
        for (int k=1; k <=200; k++)
        {
            sum += sqrt(pow(x,k+2) + pow(x,k+1) + pow(x,k) + pow(x,k -1));
        }
        vget(v,i) = sum;
    }

    const double time2 = omp_get_wtime();
    const double clock_time = time2 - time1 ;

    printf(" With %i threads , clock_time = %11.5e (sec)\n", thread_count, clock_time);
    delete_vector(&v);
    return 0;
}
void usage( const char * prog_name)
{
    fprintf(stderr, "usage : %s <thread_count > <matrix size >\n", prog_name);
    fprintf(stderr, "  thread_count should be positive \n");
    fprintf(stderr, "  N should be positive \n");
    exit(1);
}
