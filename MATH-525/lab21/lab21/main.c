# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mpi.h>
# include <math.h>
# include "matrix.h"

int main(int argc , char* argv [])
{
    // Setup MPI code
    int comm_sz , my_rank ;
    MPI_Init (NULL ,NULL);
    MPI_Comm_size ( MPI_COMM_WORLD , & comm_sz );
    MPI_Comm_rank ( MPI_COMM_WORLD , & my_rank );

    // Grab the global N parameter
    // and set the local N parameter
    int N;
    void get_input (int argc , char* argv [], const int my_rank , const int comm_sz , int* N);
    get_input (argc ,argv ,my_rank ,comm_sz ,&N); 
    //Get the size of local vector
    const int N_local = N/ comm_sz ;

    // Get time
    double time_start;
    double last_value1, last_value2, first_value1, first_value2;
    if ( my_rank ==0)
    { time_start = MPI_Wtime (); }

    // Create partial vector on current processor
    vector v_local = new_vector ( N_local );
    for (int i=1; i <= N_local ; i++)
    { vget(v_local ,i) = sqrt (( double )(i + my_rank * N_local )); }
    
    // Compute 2-norm squared
    double norm_squared;
    double norm_squared_local = pow(vget(v_local ,1) ,2);
    for (int i=2; i <= N_local ; i++)
    { norm_squared_local += pow(vget(v_local,i) ,2); }
    // Add local results to the global result on Processor 0
    if ( my_rank != 0)
    {
        MPI_Send(& norm_squared_local ,1, MPI_DOUBLE ,0,0, MPI_COMM_WORLD );
        
        //Send the last value in the "Big vector" to proc 0
        if (my_rank == comm_sz-1)
        {
            last_value1 = vget(v_local, N_local);
            MPI_Send(&last_value1 ,1, MPI_DOUBLE ,0,0, MPI_COMM_WORLD );
        }
    }
    else
    {
        norm_squared = norm_squared_local ;
        for (int i=1; i< comm_sz ; i++)
        {
            MPI_Recv (& norm_squared_local ,1, MPI_DOUBLE ,i,0, MPI_COMM_WORLD , MPI_STATUS_IGNORE );
            norm_squared += norm_squared_local ;
        }

        //Save the first and last values of "Big vetor" BEFORE computing the 2-norm
        first_value1 = vget(v_local, 1);
        MPI_Recv(&last_value1 ,1, MPI_DOUBLE ,comm_sz-1,0, MPI_COMM_WORLD , MPI_STATUS_IGNORE );
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double norm = 0.0;
    norm = sqrt(norm_squared);
    
    //Transfer the computed 2-norm from proc 0 to other procs
    printf("At first in rank %d norm is: %20.13e \n", my_rank, norm);
    if (my_rank == 0)
    {
        printf("Send 2-norm from proc 0 to other procs! \n");
	for (int i=1; i< comm_sz ; i++)
        {   
            MPI_Send(&norm ,1, MPI_DOUBLE ,i,0, MPI_COMM_WORLD );
        }
	//printf("proc 0 done ! \n");
    }
    else
    {
        MPI_Recv(&norm ,1, MPI_DOUBLE ,0,0, MPI_COMM_WORLD , MPI_STATUS_IGNORE );
        printf("Now in rank %d norm is: %20.13e \n", my_rank, norm);
    }

    
    //Divide the norm, get the new vetor

    for (int i=1; i <= N_local ; i++)
    { 
         vget(v_local ,i) = vget(v_local ,i) / norm; 
    }
    
    
    //Save first and last values of "Big vetor" AFTER computing the 2-norm
    if ( my_rank != 0)
    {
        if (my_rank == comm_sz-1)
        {
            last_value2 = vget(v_local, N_local);
            MPI_Send(&last_value2 ,1, MPI_DOUBLE ,0,0, MPI_COMM_WORLD );
        }
    }
    else
    {
        first_value2 = vget(v_local, 1);
        MPI_Recv(&last_value2 ,1, MPI_DOUBLE ,comm_sz-1,0, MPI_COMM_WORLD , MPI_STATUS_IGNORE );
    }

    // Print answer to screen
    if ( my_rank ==0)
    {
        double time_end = MPI_Wtime ();
        double time_elapsed = time_end - time_start ;
        printf (" NP = %2i, N = %i, norm_squared = %20.13e"", norm = %20.13e\n", comm_sz ,N, norm_squared , norm);
        printf (" Elapsed time = %20.13e\n", time_elapsed );
        printf ("First and last value before comuting 2-norm: %20.13e, %20.13e\n", first_value1, last_value1);
        printf ("First and last value after comuting 2-norm: %20.13e, %20.13e\n", first_value2, last_value2);
    }

    delete_vector (&v_local);

    // End program
    MPI_Finalize ();
    return 0;
}



void get_input(int argc ,char* argv[], const int my_rank, const int comm_sz, int* N)
{
    void usage(const char * prog_name);
    if (my_rank ==0)
    {
        if (argc != 2) { usage(argv[0]); }

        *N = strtol (argv[1] , NULL , 10);
        if (*N <= 0) { usage(argv[0]); }
        if (*N% comm_sz != 0) { usage(argv[0]); }

        for (int i=1; i< comm_sz; i++)
        {
        MPI_Send (N,1, MPI_INT , i,0, MPI_COMM_WORLD);
        }
        }
    else
    {
        MPI_Recv (N,1, MPI_INT ,0,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
    }
    }

void usage(const char * prog_name)
{
    fprintf(stderr, " usage : %s <N >\n",prog_name );
    fprintf(stderr, " N should be positive \n");
    fprintf(stderr, " N should be exactly divisible "   "by the number of processors \n");
    exit(1);
}

