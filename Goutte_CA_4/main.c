// main.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h"
#include "params.h" // parameter definitions
#include "init.h" // initialization of functions
#include "evolve.h" // time evolution
#include "rk4.h"
#include "forces.h"

// goal is to solve double pendulum problem
// dynamical variables are theta_1, theta_2, p_1, and p_2
// they correspond to q[0], q[1], q[2], and q[3] resp.

int main(int argc, char **argv)
{
	char *input_file; // input file name
	double *q;
	double t_i, t_f;

	input_file = argv[1];

	ReadInParams(input_file);
	PrintParams();

	// allocate memory space to q
	q = vector_malloc(PARAM_DATA.num_eq);

	InitializeNeq(q);

	printf("done init\n");

	EvolveNeq(q); // evolve q
	printf("done evolve\n");

	return 0;
} // main