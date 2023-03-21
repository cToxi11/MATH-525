#include <stdlib.h>
#include <assert.h>
#include "trimatrix.h"
#include "matrix.h"
#include <stdio.h>

double GetShift(const trimatrix* T) // get the shift value mu^(k) from A^(k) = R(k)*Q(k), to improve the convergence
{
    // get size
    const int N = T->rows; assert(N==T->cols);

    //get the new trimatix A^k = R^k * Q^k
    matrix R = new_matrix(N,N);
    mget(R,1,1) = tget(T,1,1);
    mget(R,1,2) = tget(T,1,2);
    for (int i=2; i<=(N-1); i++)
    {
        mget(R,i,i-1) = tget(T,i,i-1);
        mget(R,i,i) = tget(T,i,i);
        mget(R,i,i+1) = tget(T,i,i+1);
    }
    mget(R,N,N-1) = tget(T,N,N-1);
    mget(R,N,N) = tget(T,N,N);

    // QR factorization on bigger matrix
    matrix QRdecomp(matrix* A);
    matrix Q = QRdecomp(&R);

    // Multiply Q and R in reverse order
    // and store in a new tridiagonal matrix A

    trimatrix A = matrix_mult_to_trimatrix(&R,&Q);

    double shift = tget(&A,N,N); // set the shift mu^k = A^k[N, N]

    //delete_trimatrix(A)


    return shift;
}
