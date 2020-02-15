#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h"
#include "params.h" // parameter definitions 
#include "init.h" // initialization functions 
#include "evolve.h" // time evolution

int main(int argc, char **argv)
{

 // The goal of this assignment is to solve the Euler equations numerically 
 // The dynamical variables are q[0], q[1], q[2]
 // with the identification omega_1 = q[1], omega_2 = q[2], omega_3 = q[0] 
 // and I_1 = I[1], I_2 = I[2] and I_3 = I[0]
 // The equations to solve are
 // I_1 domega_1/dt = (I_2 - I_3)omega_2 omega_3
 // I_2 domega_1/dt = (I_3 - I_1)omega_3 omega_1
 // I_3 domega_1/dt = (I_1 - I_2)omega_1 omega_2

 char *input_file; // Input file pointer 
 double *q;
 double t_i, t_f;
 input_file = argv[1];
 ReadInParams(input_file); 
 PrintParams();

 // Previously, we stored all x(t_n) and p(t_n)
 // This time, we’ll just update x and p
 // Furthermore, we will no longer distinguish x and p to make it more general. 
 // If you do have x and p, the first half of your variables (call them q)
 // will be x and the rest p

 q = vector_malloc(PARAM_DATA.num_eq); 
 InitializeNeq(q);
 EvolveNeq(q); // this will be the workhorse
 return 0;
}// main