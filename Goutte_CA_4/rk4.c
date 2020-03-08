// rk4.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "forces.h"
#include "params.h"
#include "vector_mtx.h"
#include "rk4.h"

void RK4Step(double *q, double *q_next, FuncPt *QVelos, double t_now, 
	double h, int num_eq)
{
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

double AdaptiveRK4Step(double *q, double *q_next, FuncPt *QVelos, double t_now,
	double *t_next, double h, int num_eq)
{
	// declare variables
	double *q_full_1, *q_half;
	double err;
	double halfh = h/2.;
	double t_loc = t_now + halfh;



	// allocate memory to pointers
	q_full_1 = vector_malloc(num_eq);
	q_half = vector_malloc(num_eq);

	// take full step
	RK4Step(q, q_full_1, QVelos, t_now, h, num_eq);

	// take two half steps
	RK4Step(q, q_half, QVelos, t_now, halfh, num_eq);
	RK4Step(q_half, q_next, QVelos, t_loc, halfh, num_eq);
	// store inside q_next

	// get error estimate b/w q_full_1 and q_next
	err = EstimateError(q_full_1, q_next, t_now, h, num_eq);

	// set *t_next to t_now + h
	*t_next = t_now + h;

	// free memory space
	free(q_full_1);
	free(q_half);

	return err;

} // AdaptiveRK4Step

double EstimateError(double *q_full, double *q_next, double t_now, 
	double h, int num_eq)
{
	// declare
	double err;

	// calculate distance
	err = Vector_Distance(q_full, q_next, num_eq);

	// divide by 15
	err /= 15;

	return err;
} // EstimateError

double EstimateNextH(double err, double err0, double h)
{
	// to make sure that h is small enough
	// introduce "factor" and set it to 0.5
	double factor = 0.5;

	// declare variables
	double h_new;

	h_new = h*pow((factor*err0/err),0.2);

	return h_new;
} // EstimateNextH

























