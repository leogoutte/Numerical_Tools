#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include "vector_mtx.h"

int main() 
{
 double *v, *u, **mtx, x;
 int nmax, mmax, n, m;
 FILE *output;

 nmax = 100;
 mmax = 45;

 v = vector_malloc(mmax);
 u = vector_malloc(mmax);
 mtx = mtx_malloc(mmax, nmax);

 for(m=0; m<mmax; m++)
  {
   for(n=0; n<nmax; n++)
    {
     mtx[m][n] = 1.0/(m + n + 1.0); // some number 
    }
   v[m] = sin(m*0.1); // some number 
  }// m

 output = fopen("GOUTTE_test1.dat","w"); 
 for(m=0; m<mmax; m++)
  {
   x = m*0.1;
   fprintf(output, "%e %e %e\n", x, v[m], sin(m*0.1));
  }
 fclose(output);

 output = fopen("GOUTTE_test2.dat","w"); 
 m = 20.0; // set m=20.0 to be able to plot in 2D                                                  // plot in 2d
 for(n=0; n<nmax; n++)
  {
   fprintf(output, "%d %e %e\n", n, mtx[m][n], 1.0/(m + n + 1.0));
  }
 fclose(output);

 CopyVector(v, u, mmax);

 x = 0.0;
 for(m=0; m<mmax; m++)
  {
   x += fabs(v[m] - u[m]); // sum |v[m] - u[m]|
  }// m

 printf("This should be 0: %21.15e\n", x);

 free(u); // Always free up allocated memory after use 
 free(v); // If you do not do this, it will often lead to 
 mtx_free(mtx, mmax); // what’s commonly known as "memory leak"
 return 0;
}// main
