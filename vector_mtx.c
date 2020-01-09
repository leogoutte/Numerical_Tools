#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h"

int m, n;

// implement functions from header file

// vector memory alloc
double *vector_malloc(int nmax) {
    double *vec; //pointer to a double precision variable
    vec = (double*)malloc(sizeof(double)*nmax);
    return vec;
}

// matrix memory alloc
double **mtx_malloc(int mmax, int nmax) {
    double **mtx; //pointer to pointer
    mtx = (double**)malloc(sizeof(double*)*mmax);
    for (m=0; m<mmax; m++) //loop through rows
    {
        mtx[m] = (double*)malloc(sizeof(double)*nmax); 
        // allocate 1-D vector to each row
        // each row is a 1-D vector with nmax elements
    }
    return mtx;
}

// matrix memory de-allocation
void mtx_free(double **mtx, int mmax) {
    for (m=0; m<mmax; m++) 
    {
        free(mtx[m]);
    }
    free(mtx);
}

// copy vector a to b (b becomes a)
void CopyVector(double *a, double *b, int nmax) {
    for (n=0; n<nmax; n++)
    {
        b[n] = a[n];
    }
}

// integer operation
int *int_vector_malloc(int nmax) {
    int *integer;
    integer = (int*)malloc(nmax);
    return integer;
}