// vector_mtx.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h"

// implement functions from header file

// vector memory alloc
double *vector_malloc(int nmax) 
{
    double *vec; //pointer to a double precision variable
    vec = (double*)malloc(sizeof(double)*nmax); // allocate memory
    // initialize the vector
    for (int i=0; i<nmax; i++)
    {
        vec[i] = 0.0;
    }
    return vec;
} //def

// matrix memory alloc
double **mtx_malloc(int mmax, int nmax) 
{
    double **mtx; //pointer to pointer
    mtx = (double**)malloc(sizeof(double*)*mmax); //allocate memory for cols
    for (int i=0; i<mmax; i++) //loop through rows
    {
        mtx[i] = (double*)malloc(sizeof(double)*nmax); //allocate memory for rows
        // each row is a 1-D vector with nmax elements
    } 
    //initialize the matrix
    for(int i=0; i<mmax; i++)
    {
        for(int j=0; j<nmax; j++)
        {
            mtx[i][j] = 0.0;
        } // j-loop
    } // i-loop
    return mtx;
} //def

// matrix memory de-allocation
void mtx_free(double **mtx, int mmax) 
{
    for (int i=0; i<mmax; i++)
    {
        free(mtx[i]); //free up the row vectors
    }
    free(mtx); // free up the pointers to the row vectors
} //def

// copy vector a to b (b becomes a)
void Vector_Copy(double *a, double *b, int nmax) 
{
    for (int i=0; i<nmax; i++)
    {
        b[i] = a[i]; // paste the values of a onto b
    }
} //def

// integer operation 
// same as vect_malloc but only integer values
int *int_vector_malloc(int nmax) 
{
    int *integer;
    integer = (int*)malloc(sizeof(int)*nmax);
    // initialize the vector
    for (int i=0; i<nmax; i++)
    {
        integer[i] = 0; // integers
    }
    return integer;
} //def

void Vector_APlusScaledBtoA(double *a, double *b, double c, int nmax)
{
    for (int i = 0; i < nmax; ++i)
    {
        a[i] = a[i] +c*b[i]; // put back into a
    }
    return;
} // Vector_APlusScaledBtoA

void Vector_Clear(double *a, int nmax)
{
    for (int i = 0; i < nmax; ++i)
    {
        a[i] = 0; // clear each element
    }
    return;
} // Vector_Clear

double Vector_Distance(double *a, double *b, int num_elems)
{
    double sum, dist, diff;
    sum = 0.; // initialize
    for (int i = 0; i < num_elems; i++)
    {
        diff = a[i] - b[i];
        sum += pow(diff, 2); // sum over all "dimensions"
    }
    dist = pow(sum, 0.5);
    return dist;
} // Vector_Distance




