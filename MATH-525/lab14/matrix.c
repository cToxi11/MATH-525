#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"


matrix new_matrix(const int rows, const int cols)
{
    matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    assert(rows>0);
    assert(cols>0);
    mat.val = (double*)malloc(sizeof(double)*rows*cols);
    for (int i=0; i<(rows*cols); i++)
    { mat.val[i] = 0.0; }
    return mat;
}

vector new_vector(const int size)
{
    vector vec;
    vec.size = size;
    assert(size>0);
    vec.val = (double*)malloc(sizeof(double)*size);

    for (int i=0; i<(size); i++)
    { vec.val[i] = 0.0; }

    return vec;
}


void print_matrix_full(const matrix* mat, char* varname)
{
    assert(mat->rows>0); assert(mat->cols>0);
    printf("\n %.100s =\n", &varname[1] );
    for(int i=1; i<=mat->rows; i++ )
    {
        printf(" | ");
        for(int j=1; j<=mat->cols; j++)
        {
            printf("%10.3e",mgetp(mat,i,j));
            if (j<mat->cols) {printf(", ");}
            else {printf(" ");}
        }
        printf("|\n");
    }
    printf("\n");
}

void print_vector_full(const vector* vec, char* varname)
{
    assert(vec->size>0);
    printf("\n");
    printf(" %.100s =\n", &varname[1] );
    printf(" | ");
    for(int i=1; i<=vec->size; i++ )
    {
        printf("%10.3e",vgetp(vec,i));
        if (i<vec->size) {printf(", ");}
    }
    printf(" |^T\n\n");
}


matrix matrix_mult(const matrix* A, const matrix* B)
{
    const int rowsA = A->rows; const int colsA = A->cols;
    const int rowsB = B->rows; const int colsB = B->cols;
    assert(colsA==rowsB);
    matrix C = new_matrix(rowsA,colsB);

    for (int i=1; i<=rowsA; i++)
        for (int j=1; j<=colsB; j++)
            for (int k=1; k<=colsA; k++)
            {
                mget(C,i,j) += mgetp(A,i,k)*mgetp(B,k,j);
            }

    return C;
}

matrix matrix_trans(const matrix* A)
{
    const int rowsA = A->rows; const int colsA = A->cols;
    matrix C = new_matrix(rowsA,colsA);
    for (int i=1; i<=rowsA; i++)
        for (int j=1; j<=colsA; j++)
        {
            mget(C,i,j) = mgetp(A,j,i);
        }

    return C;
}

double vector_norm(const vector* vec)
{
    double norm = 0.0;
    for (int i = 1; i <=vec->size; i++) {
        norm += vgetp(vec,i) * vgetp(vec,i);
    }
    return sqrt(norm);
}

vector vector_div_scalar(const vector* x, const double scalar)
{
    const int size = x->size;
    vector z = new_vector(size);
    for (int i = 1; i <=size; i++) {
        vget(z,i) = vgetp(x,i) / scalar;
    }
    return z;
}

double vector_dot_mult(const vector* x, const vector* y)
{
    const int size = x->size; assert(size==y->size);

    double z = 0.0;
    for (int i=1; i<=size; i++)
    { z += vgetp(x,i)*vgetp(y,i); }

    return z;
}

matrix matrix_minus_muI(const matrix* A, const double mu)
{
    const int rows = A->rows; const int cols = A->cols;

    matrix C = new_matrix(rows,cols);

    for (int i=1; i<=rows; i++)
        for (int j=1; j<=cols; j++)
        {
            if (i==j){
                mget(C,i,j) = mgetp(A,i,j)-mu;
            }
            else{
                mget(C,i,j) = mgetp(A,i,j);
            }

        }

    return C;
}


vector matrix_vector_mult(const matrix* A, const vector* x)
{
    const int rows = A->rows; const int cols = A->cols;
    const int size = x->size;
    assert(cols==size);
    vector Ax = new_vector(rows);

    for (int i=1; i<=rows; i++)
    {
        double tmp = 0.0;
        for (int j=1; j<=size; j++)
        { tmp += mgetp(A,i,j)*vgetp(x,j); }
        vget(Ax,i) = tmp;
    }

    return Ax;
}


vector solve(const matrix* A, const vector* b)
{
    const int rows = A->rows; const int cols = A->cols;
    const int size = b->size;
    assert(rows==cols); assert(rows==size);

    vector x = new_vector(rows);

    for (int i=1; i<=(size-1); i++) // LOOP OVER EACH COLUMN
    {
        // Select largest pivot in current column
        int p=i; double maxA = -100.0e0;
        for (int j=i; j<=size; j++)
        {
            double tmp = fabs(mgetp(A,j,i));
            if ( tmp > maxA ){ p = j; maxA = tmp; }
        }

        // See if matrix is singular
        if (maxA <= 1.0e-14)
        { printf(" Cannot invert system\n"); exit(1); }
        // Pivot (aka interchange rows)
        if (p!=i)
        {
            for (int j=1; j<=size; j++)
            {
                double tmp1 = mgetp(A,i,j);
                mgetp(A,i,j) = mgetp(A,p,j); mgetp(A,p,j) = tmp1;
            }

            double tmp2 = vgetp(b,i);
            vgetp(b,i) = vgetp(b,p); vgetp(b,p) = tmp2;
        }

        // Eliminate below diagonal
        for (int j=(i+1); j<=size; j++)
        {
            double dm = mgetp(A,j,i)/mgetp(A,i,i);
            for (int k=1; k<=size; k++)
            { mgetp(A,j,k) = mgetp(A,j,k) - dm*mgetp(A,i,k); }
            vgetp(b,j) = vgetp(b,j) - dm*vgetp(b,i);
        }
    }
    // Backward substitution
    vget(x,size) = vgetp(b,size)/mgetp(A,size,size);
    for (int j=1; j<=(size-1); j++)
    {
        double sum = 0.0e0;

        for (int k=(size-j+1); k<=size; k++)
        { sum = sum + mgetp(A,size-j,k)*vget(x,k); }

        vget(x,size-j) = (vgetp(b,size-j) - sum)/mgetp(A,size-j,size-j);
    }

    return x;
}

void PowerIter(const matrix* A, const vector* v, const int MaxIters, const double TOL)
{
    const int rows = A->rows; const int cols = A->cols;
    const int size = v->size;
    assert(rows==cols); assert(rows==size);

    int mstop = 0; int k = 0; double lamda = 0; double new_lamda = 0; //initialization part
    double norm_v = vector_norm(v);
    //printf("%f", norm_v);
    vector v_current = vector_div_scalar(v, norm_v);
    vector Av = matrix_vector_mult(A, &v_current);
    lamda = vector_dot_mult(&v_current, &Av);
    //printf("lamda: %f\n ", lamda);
    //print_vector(&v_current);


    while (mstop == 0){ //iteration part
        k = k + 1;
        vector w = matrix_vector_mult(A, &v_current);
        //print_vector(&w);
        double norm_w = vector_norm(&w);
        //printf("norm_w == %f \n", norm_w);
        vector v_current = vector_div_scalar(&w, norm_w);
        //print_vector(&v_current);
        vector Av = matrix_vector_mult(A, &v_current);
        new_lamda = vector_dot_mult(&v_current, &Av);
        //printf("new lamda: %f\n ", new_lamda);
        //printf("new lamda - lamda : %f\n ", new_lamda-lamda);
        if (fabs(new_lamda - lamda) < TOL || k == MaxIters) // check if meet the stop criteria
        {
            //printf("fabs new lamda - lamda : %f and TOL %f \n", fabs(new_lamda-lamda), TOL);
            mstop = 1;
        }
        lamda = new_lamda;
    }
    printf("!!! Stop at %i th iteration, where lamda equal to %f \n", k, new_lamda);

}

void Shifted_Inverse(const matrix* A, const vector* v, const int MaxIters, const double TOL, const double mu)
{
    const int rows = A->rows; const int cols = A->cols;
    const int size = v->size;
    assert(rows==cols); assert(rows==size);

    int mstop = 0; int k = 0; double lamda = 0; double new_lamda = 0; //initialization part
    double norm_v = vector_norm(v);
    //printf("%f", norm_v);
    vector v_current = vector_div_scalar(v, norm_v);
    vector Av = matrix_vector_mult(A, &v_current);
    lamda = vector_dot_mult(&v_current, &Av);
    matrix A_m = matrix_minus_muI(A, mu);
    //printf("lamda: %f\n ", lamda);
    //print_vector(&v_current);


    while (mstop == 0){ //iteration part
        k = k + 1;
        vector w = solve(&A_m, &v_current);
        //print_vector(&w);
        double norm_w = vector_norm(&w);
        //printf("norm_w == %f \n", norm_w);
        vector v_current = vector_div_scalar(&w, norm_w);
        //print_vector(&v_current);
        vector Av = matrix_vector_mult(A, &v_current);
        new_lamda = vector_dot_mult(&v_current, &Av);
        //printf("new lamda: %f\n ", new_lamda);
        //printf("new lamda - lamda : %f\n ", new_lamda-lamda);
        if (fabs(new_lamda - lamda) < TOL || k == MaxIters) // check if meet the stop criteria
        {
            //printf("fabs new lamda - lamda : %f and TOL %f \n", fabs(new_lamda-lamda), TOL);
            mstop = 1;
        }
        lamda = new_lamda;
    }
    printf("!!! Stop at %i th iteration, where lamda equal to %f \n", k, new_lamda);

}

void Rayleigh_Quotient(const matrix* A, const vector* v, const int MaxIters, const double TOL)
{
    const int rows = A->rows; const int cols = A->cols;
    const int size = v->size;
    assert(rows==cols); assert(rows==size);

    int mstop = 0; int k = 0; double lamda = 0; double new_lamda = 0; //initialization part
    double norm_v = vector_norm(v);
    vector v_current = vector_div_scalar(v, norm_v);
    vector Av = matrix_vector_mult(A, &v_current);
    lamda = vector_dot_mult(&v_current, &Av);

    while (mstop == 0){ //iteration part
        k = k + 1;
        matrix A_lamda = matrix_minus_muI(A, lamda);
        vector w = solve(&A_lamda, &v_current);
        double norm_w = vector_norm(&w);
        vector v_current = vector_div_scalar(&w, norm_w);
        vector Av = matrix_vector_mult(A, &v_current);
        new_lamda = vector_dot_mult(&v_current, &Av);
        if (fabs(new_lamda - lamda) < TOL || k == MaxIters) // check if meet the stop criteria
        {
            mstop = 1;
        }
        lamda = new_lamda;
    }
    printf("!!! Stop at %i th iteration, where lamda equal to %f \n", k, new_lamda);

}
