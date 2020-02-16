// evolve.c
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include "evolve.h" 
#include "forces.h" 
#include "params.h" 
#include "vector_mtx.h" 
#include "analysis.h"

// evolve q
void EvolveNeq(double *q)
{
	int it, it_max, i, num_eq, count;
	double t_now, t_i, h, t_f, t_next; 
	FuncPt *QVelos; // To pass onto another function 
	double *q_next, *q_tmp;
	FILE *output;

	// initialize data
	t_i = PARAM_DATA.t_i;
	t_f = PARAM_DATA.t_f;
	it_max = PARAM_DATA.it_max;
	h = PARAM_DATA.h;
	num_eq = PARAM_DATA.num_eq;

	// if t_f < t_i, warn and exit
	if (t_f < t_i)
	{
		fprintf(stderr, "Initial time is greater than final time\n");
		exit(1); // exit
	}

	// assign PARAM_DATA.QVelos to QVelos
	QVelos = PARAM_DATA.QVelos; // QVelos is assigned memory in init.c

	// make a q_next vector
	q_next = vector_malloc(num_eq);

	// open output file for writing
	output = fopen("coordinates.dat", "w"); // _100 for it_max = 100

	// initialize time
	t_now = t_i;

	// evolve
	for(it = 0; it<it_max; it++)
	{
		// record dynamical variables at t_now
		RecordAStep(output, t_now, q, num_eq);

		// RK4 evolution
		RK4Step(q, q_next, QVelos, t_now, h, num_eq);

		// copy q_next to q by swapping memory places
		q_tmp = q;
		q = q_next;
		q_next = q_tmp;

		// advance in time for next iteration
		t_now = t_now + h;
	} // it-loop
	RecordAStep(output, t_now, q, num_eq); // for results at t_f

	// close file
	fclose(output);

	return;
} // EvolveNeq

void RecordAStep(FILE *output, double t_now, double *q, int num_eq)
{
	double ene;
	ene = KineticEnergy(q);

	// add t_now
	fprintf(output, "%lf ", t_now);

	// add q's w/o skipping a line
	int i;
	for (i=0; i<num_eq; i++)
	{
		fprintf(output, "%lf ", q[i]);
	}
	// add KE
	fprintf(output, "%lf\n", ene);

	return;
} // RecordAtStep

void OneStepNeq(double *q_now, double *q_in, double *q_next, FuncPt *QVelos, 
	double t_in, double h, int num_eq)
{
	int i; // looping index

	// loop over index to calculate q_next
	for (i=0; i<num_eq; i++)
	{
		q_next[i] = q_now[i] + h*(*QVelos[i])(q_in, t_in, num_eq);
		// since QVelos is itself a vector (QVelo0, QVelo1, etc...)
	}

	return;
} // OneStepNeq

void RK4Step(double *q, double *q_next, FuncPt *QVelos, double t_now, 
	double h, int num_eq)
{
	int n;
	double t_half, t_next;
	static int ind = 0; 			// static variables do not change between
	static double *q_local, *q_sum; // function calls

	// count how many times function is called
	ind++;

	if (ind == 1) // first time it is called we must allocate memory
	{
		q_local = vector_malloc(num_eq);
		q_sum = vector_malloc(num_eq);
	}

	// set times
	t_half = t_now + h/2;
	t_next = t_now + h;

	// initialize sum
	Vector_Clear(q_sum, num_eq);

	// RK the first step
	// note time variable must match step
	OneStepNeq(q, q, q_local, QVelos, t_now, 0.5*h, num_eq);

	// We need 1/3 of the first vector
	Vector_APlusScaledBtoA(q_sum, q_local, 1.0/3.0, num_eq);

	// RK second step
	OneStepNeq(q, q_local, q_next, QVelos, t_half, 0.5*h, num_eq);

	// add 2/3 of the second vector to q_sum
	Vector_APlusScaledBtoA(q_sum, q_next, 2.0/3.0, num_eq);

	// RK third step
	OneStepNeq(q, q_next, q_local, QVelos, t_half, h, num_eq);

	// add 1/3 of the third vector to q_sum
	Vector_APlusScaledBtoA(q_sum, q_local, 1.0/3.0, num_eq);

	// RK fourth step
	OneStepNeq(q, q_local, q_next, QVelos, t_next, h, num_eq);

	// add 1/6 of the fourth vector to q_sum
	Vector_APlusScaledBtoA(q_sum, q_next, 1.0/6.0, num_eq);

	// add -1/2 of q to q_sum
	Vector_APlusScaledBtoA(q_sum, q, -1.0/2.0, num_eq);

	// copy q_sum to q_next
	Vector_Copy(q_sum, q_next, num_eq);

	return;
} // RK4 step



















