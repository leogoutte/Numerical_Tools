// File main.c
// This file should only contain the main function
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h" // vector and matrix utility functions 
#include "params.h" 	// parameter definitions
#include "init.h" // initialization functions
#include "evolve.h" // time evolution
#include "analysis.h" // analyze the results

int main(int argc, char **argv)
{
 char *input_file; // Input file name 
 double *x, *p;
 input_file = argv[1];

 // These two functions from assignment 1 
 // should be in good working condition 
 ReadInParams(input_file); // makes PARAM_DATA callable
 PrintParams();

 // The vector_malloc function from assignment 1 
 // should also be in good working condition
 x = vector_malloc(PARAM_DATA.it_max + 1); // make x vector
 p = vector_malloc(PARAM_DATA.it_max + 1); // make p vector

 // Initialize x and p
 Initialize(x, p);

 // Evolve x and p
 Evolve(x, p);

 // This is in analysis.h and analysis.c 
 WriteResults(x, p);

 return 0;
} // main