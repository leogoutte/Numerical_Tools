// Vector matrix header
#ifndef VECTOR_MTX_H
#define VECTOR_MTX_H
// These ensure that each header file is included only once 
// If this header was previously included by another header 
// then VECTOR_MTX_H is already defined.
// In that case, we jump to the last line and skip the content
double *vector_malloc(int nmax); // vector memory allocation
                                 // index runs from 0 to nmax-1
double **mtx_malloc(int mmax, int nmax); // matrix memory allocation
                                         // indices run from 0 to mmax-1
                                         // and 0 to nmax-1
void mtx_free(double **mtx, int mmax); // matrix memory de-allocation
void CopyVector(double *a, double *b, int nmax); // copy a to b. the index runs from 0 to nmax-1
                                                 // integer operations
int *int_vector_malloc(int nmax); // integer vector allocation
#endif // ensures that each header file is included only once