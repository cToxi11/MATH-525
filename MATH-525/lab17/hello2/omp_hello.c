# include <stdio.h>
# include <stdlib.h>
# ifdef _OPENMP
#   include <omp.h>
# endif

//# include <omp.h>

int main(int argc , char* argv [])
8 {
9 void usage ( const char* prog_name );
10 void hello ( const int thread_count );
11
12 if (argc != 2) { usage (argv [0]); }
13 const int thread_count = strtol (argv [1] , NULL , 10);
14 if ( thread_count <= 0)
15 { usage (argv [0]); }
16
17 printf ("\n");
18 # pragma omp parallel num_threads ( thread_count )
19 hello ( thread_count );
20 printf ("\n");
21
22 return 0;
23 } 23
void usage ( const char * prog_name )
2 {
3 fprintf (stderr , "usage : %s <thread_count >\n", prog_name );
4 fprintf (stderr , " thread_count should be positive \n");
5 exit (1);
6 }
7 void hello ( const int thread_count )
8 {
9 # ifdef _OPENMP
10 const int my_rank = omp_get_thread_num ();
11 const int actual_thread_count = omp_get_num_threads ();
12 # else
13 const int my_rank = 0;
14 const int actual_thread_count = 1;
15 # endif
16 if ( my_rank == 0 && thread_count != actual_thread_count )
17 {
18 fprintf (stderr , " Number of threads started != %i\n",
19 thread_count );
20 }
21 printf (" Hello from thread %i of %i\n", my_rank +1,
22 actual_thread_count );
23 } 24