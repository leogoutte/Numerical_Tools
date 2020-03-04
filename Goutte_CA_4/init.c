// init.c
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include "params.h"  // PARAM_DATA
#include "init.h" 
#include "vector_mtx.h"
#include "forces.h"

// populate params in PARAM_DATA

void ReadInParams(char *input_file)
{
	double xd; // scanning variables
	int xi; // ditto for integers
	int nidx;
	double *I_prin, *q_i; // vectors for body frame I and q

	FILE *input; // pointer to a file

	input = fopen(input_file, "r"); // open file to read

	// read in number of eqs
	fscanf(input, "%d", &xi);
	PARAM_DATA.num_eq = xi;

	nidx = PARAM_DATA.num_eq; // max indexing

	// allocate memories for initial coordinates vector
	q_i = vector_malloc(nidx);

	// q
	for (int i=0; i<nidx; i++)
	{
		fscanf(input, "%lf", &xd);
		q_i[i] = xd;
	}

	PARAM_DATA.q_i = q_i; // put q_i vector into PARAM_DATA

	// t_i
	fscanf(input, "%lf", &xd);
	PARAM_DATA.t_i = xd;

	// t_f
	fscanf(input, "%lf", &xd);
	PARAM_DATA.t_f = xd;

	// h
	fscanf(input, "%lf", &xd);
	PARAM_DATA.h = xd;

	// mass 1
	fscanf(input, "%lf", &xd);
	PARAM_DATA.mass1 = xd;

	// length 1
	fscanf(input, "%lf", &xd);
	PARAM_DATA.length1 = xd;

	// mass 2
	fscanf(input, "%lf", &xd);
	PARAM_DATA.mass2 = xd;

	// length 2
	fscanf(input, "%lf", &xd);
	PARAM_DATA.length2 = xd;

	// prec_goal
	fscanf(input, "%lf", &xd);
	PARAM_DATA.prec_goal = xd;	
	
	fclose(input);

	return;
} // ReadInParams

void PrintParams(void)
{
	int nidx = PARAM_DATA.num_eq; // to loop over vectors
	FILE *output;
	output = fopen("params.dat", "w"); // open file to write vals onto
	{
		fprintf(output, "Number of coordinates: %d\n", PARAM_DATA.num_eq);

		fprintf(output, "Theta 1: %lf\n", PARAM_DATA.q_i[0]);

		fprintf(output, "Theta 2: %lf\n", PARAM_DATA.q_i[1]);

		fprintf(output, "Momentum 1: %lf\n", PARAM_DATA.q_i[2]);

		fprintf(output, "Momentum 2: %lf\n", PARAM_DATA.q_i[3]);

		fprintf(output, "Initial time: %lf\n", PARAM_DATA.t_i);

		fprintf(output, "Final time: %lf\n", PARAM_DATA.t_f);

		fprintf(output, "Default timestep: %lf\n", PARAM_DATA.h);

		fprintf(output, "Mass 1: %lf\n", PARAM_DATA.mass1);

		fprintf(output, "Mass 2: %lf\n", PARAM_DATA.mass2);

		fprintf(output, "Length 1: %lf\n", PARAM_DATA.length1);

		fprintf(output, "Length 2: %lf\n", PARAM_DATA.length2);

		fprintf(output, "Precision goal: %lf\n", PARAM_DATA.prec_goal);

	} // done writing
	fclose(output);

	// print onto terminal
	printf("Initial Params:\n");
	printf("num_eq = %d\n", PARAM_DATA.num_eq);
	for (int i = 0; i < nidx; ++i)
	{
		printf("%lf\n", PARAM_DATA.q_i[i]);
	}
	printf("t_i = %lf\n", PARAM_DATA.t_i);
	printf("t_f = %lf\n", PARAM_DATA.t_f);
	printf("h = %lf\n", PARAM_DATA.h);
	printf("mass1 = %lf\n", PARAM_DATA.mass1);
	printf("length1 = %lf\n", PARAM_DATA.length1);
	printf("mass2 = %lf\n", PARAM_DATA.mass2);
	printf("length2 = %lf\n", PARAM_DATA.length2);
	printf("prec_goal = %lf\n", PARAM_DATA.prec_goal);

	return;
} // PrintParams

void InitializeNeq(double *q)
{
	int nidx = PARAM_DATA.num_eq;

	// q is already declared and memory is already allocated
	for (int i=0; i<nidx; i++) // fill up q with initial data
	{
		q[i] = PARAM_DATA.q_i[i];
	} // i-loop

	// assign memory to QVelos
	PARAM_DATA.QVelos = (FuncPt *)malloc(sizeof(FuncPt)*nidx);

	// problem specific
	// have 4 generalized velocities
	PARAM_DATA.QVelos[0] = QVelo0;
	PARAM_DATA.QVelos[1] = QVelo1;
	PARAM_DATA.QVelos[2] = QVelo2;
	PARAM_DATA.QVelos[3] = QVelo3;

	return;
} // InitializeNeq






