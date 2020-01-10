#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h"

// implement functions from header file

// vector memory alloc
double *vector_malloc(int nmax) 
{
    double *vec; //pointer to a double precision variable
    vec = (double*)malloc(sizeof(double)*nmax);
    // initialize the vector
    for (int i=0; i<nmax; i++)
    {
        vec[i] = 0.0;
    }
    return vec;
}

// matrix memory alloc
double **mtx_malloc(int mmax, int nmax) 
{
    double **mtx; //pointer to pointer
    mtx = (double**)malloc(sizeof(double*)*mmax);
    for (int i=0; i<mmax; i++) //loop through rows
    {
        mtx[i] = (double*)malloc(sizeof(double)*nmax); 
        // allocate 1-D vector to each row
        // each row is a 1-D vector with nmax elements
    }
    //initialize the matrix
    for(int i=0; i<mmax; i++)
    {
        for(int j=0; j<nmax; j++)
        {
            mtx[i][j] = 0.0;
        }
    }// m-loop
    return mtx;
}

// matrix memory de-allocation
void mtx_free(double **mtx, int mmax) 
{
    for (int i=0; i<mmax; i++) 
    {
        free(mtx[i]);
    }
    free(mtx);
}

// copy vector a to b (b becomes a)
void CopyVector(double *a, double *b, int nmax) 
{
    for (int i=0; i<nmax; i++)
    {
        b[i] = a[i];
    }
} 

// integer operation
int *int_vector_malloc(int nmax) 
{
    int *integer;
    integer = (int*)malloc(sizeof(int)*nmax);
    // initialize the vector
    for (int i=0; i<nmax; i++)
    {
        integer[i] = 0;
    }
    return integer;
}