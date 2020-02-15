// init.c
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include "params.h"  // PARAM_DATA
#include "init.h" 
#include "vector_mtx.h"

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

	// it_max
	fscanf(input, "%d", &xi);
	PARAM_DATA.it_max = xi;

	// h
	xd = (PARAM_DATA.t_f - PARAM_DATA.t_i)/((double) PARAM_DATA.it_max);
	PARAM_DATA.h = xd;

	// allocate memories for principal moments vector
	I_prin = vector_malloc(nidx);

	// I_prin
	for (int i=0; i<nidx; i++)
	{
		fscanf(input, "%lf", &xd);
		I_prin[i] = xd;
	}

	PARAM_DATA.I_prin = I_prin; // put vector into PARAM_DATA
	fclose(input);

	return;
} // ReadInParams

void PrintParams(void)
{
	int nidx = PARAM_DATA.num_eq; // to loop over vectors
	FILE *output;
	output = fopen("params.dat", "w"); // open file to write vals onto
	{
		fprintf(output, "%d\n", PARAM_DATA.num_eq);

		for (int i=0; i<nidx; i++) // loop over all q_i vals
		{
			fprintf(output, "%lf\n", PARAM_DATA.q_i[i]);
		} // i-loop

		fprintf(output, "%lf\n", PARAM_DATA.t_i);

		fprintf(output, "%lf\n", PARAM_DATA.t_f);

		fprintf(output, "%d\n", PARAM_DATA.it_max);

		fprintf(output, "%lf\n", PARAM_DATA.h);

		for (int i=0; i<nidx; i++) // loop over all I_prin vals
		{
			fprintf(output, "%lf\n", PARAM_DATA.I_prin[i]);
		} // i-loop
	} // done writing
	fclose(output);

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

	PARAM_DATA.QVelos = (FuncPt *)malloc(sizeof(FuncPt)*num_eq); // assign memory

	// problem specific
	// cannot modularize since exactly three different QVeloi in forces.h, .c
	PARAM_DATA.QVelos[0] = QVelo0;
	PARAM_DATA.QVelos[1] = QVelo1;
	PARAM_DATA.QVelos[2] = QVelo2;

	return;
} // InitializeNeq






