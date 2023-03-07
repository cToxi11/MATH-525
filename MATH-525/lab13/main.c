#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

int main()
{
    // Matrices
    matrix L = new_matrix(5,5);
    matrix LT = new_matrix(5,5);

    for(int i=1; i<=5; i++ )
    {
        for (int j=1; j<=i; j++ )
        {
            mget(L,i,j) = (double) rand() / RAND_MAX;
        }
        mget(L,i,i) = 1; // set diagonal element to 1
        for (int j=i+1; j<=5; j++ )
        {
            mget(L,i,j) = 0; // set upper triangular elements to 0
        }
    }

    // compute transpose of L
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            mget(LT,i,j) = mget(L,j,i);
        }
    }

    matrix A = matrix_mult(&L,&LT);
    // Print matrices
    print_matrix(&L);
    print_matrix(&LT);
    print_matrix(&A);

    // Vectors
    vector b = new_vector(5);

    vget(b,1) = (double) rand() / RAND_MAX;
    vget(b,2) = (double) rand() / RAND_MAX;
    vget(b,3) = (double) rand() / RAND_MAX;
    vget(b,4) = (double) rand() / RAND_MAX;
    vget(b,5) = (double) rand() / RAND_MAX;

    // Print vectors
    print_vector(&b);

    // Linear solve via Gaussian elimination
    vector soln = solve(&A,&b);
    print_vector(&soln);
}

