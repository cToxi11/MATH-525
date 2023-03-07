#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

int main()
{
    // create an example matrix
    matrix A = new_matrix(3,3);
    mget(A,1,1) = 1; mget(A,1,2) = 2; mget(A,1,3) = 3;
    mget(A,2,1) = 1; mget(A,2,2) = 2; mget(A,2,3) = 1;
    mget(A,3,1) = 1; mget(A,3,2) = 2; mget(A,3,3) = 3;

    // Print matrices
    print_matrix(&A);

    // Create a example Vector
    vector v = new_vector(3);

    vget(v,1) = 1;
    vget(v,2) = 1;
    vget(v,3) = 1;

    // Print vectors
    print_vector(&v);

    int MaxIters = 100; double TOL = 1.0e-6;

    PowerIter(&A, &v, MaxIters, TOL);

}

