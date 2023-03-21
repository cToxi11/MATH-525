#include <stdlib.h>
#include <assert.h>
#include "trimatrix.h"
#include <stdio.h>
#include <math.h>


int FindZero(const trimatrix* T)
// try to find a k that T[k, k+1] and T[k+1, k] = 0 (or < TOL = 1.0e-6) and return k; if the answer is no, return T->rows
{
    // get size
    const int N = T->rows; assert(N==T->cols);


    int k = 1; // initialize the k

    while (k < N){
        if ( fabs(tget(T,k+1,k)) < 1.0e-14) {return k;} // here we only need to check one value since T is a symmetric matrix
        k = k + 1;
    }
    //printf("k now: %i\n", k);
    return k;

}
