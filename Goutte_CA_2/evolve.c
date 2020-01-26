// This file is evolve.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "evolve.h"
#include "forces.h"

// implement evolve/solvers

// Evolve
void Evolve(double *x, double *p)
{
	int it, it_max, choice;

	it_max = PARAM_DATA.it_max; // get it_max from input PARAMS_DATA
	choice = PARAM_DATA.choice; // get choice from input

	for(it=0; it<it_max; it++)
	{
		AdvanceOneStep(x, p, it, choice);
	} // it-loop

	return;
} // Evolve

// Advance
void AdvanceOneStep(double *x, double *p, int it_now, int choice)
{
	// define variables
	double x_now, p_now, x_next, p_next; 
	double v, f, h;
	int it_next;

	// get "current" values
	x_now = x[it_now];
	p_now = p[it_now];

	// get h from input
	h = PARAM_DATA.h;

	// from t_{n+1} = t_{n} + h, set it_next = it_now + 1
	it_next = it_now + 1;

	// depending on choice, implement algorithm

	if (choice == 1) // forward euler
	{
		ForwardEulerStep(x_now, p_now, &x_next, &p_next, h);
	}

	else if (choice == 2) // backward euler
	{
		BackwardEulerStep(x_now, p_now, &x_next, &p_next, h);
	}

	else if (choice == 3) // leapfrog 1 (x_{1/2})
	{
		Leapfrog1Step(x_now, p_now, &x_next, &p_next, h);
	}

	else if (choice == 4) // leapfrog 2 (p_{1/2})
	{
		Leapfrog2Step(x_now, p_now, &x_next, &p_next, h);
	}

	else
	{
		fprintf(stderr, "choice = %d is not yet implemented. \n", choice);
		exit(1);
	}

	// store obtained values
	x[it_next] = x_next;
	p[it_next] = p_next;

	return;
} // Advance

// Implement OneStep

void OneStep(double x_now, double p_now, double x_in, double p_in, double *x_next, double *p_next, double h)
{
	double x, p;

	// take step forward
	x = x_now + h*Velocity(p_in); // p_in not necessarily p_now
	p = p_now + h*Force(x_in); // ditto for x

	// put as values of x_next, p_next by dereferencing
	*x_next = x;
	*p_next = p;

	return; 
} // OneStep

// Implement ForwardEulerStep (gien in PS)

void ForwardEulerStep(double x_now, double p_now, double *x_next, double *p_next, double h)
{
	double x, p;

	// do OneStep with x_in = x_now and p_in = p_now
	OneStep(x_now, p_now, x_now, p_now, x_next, p_next, h); 

	return;
} // ForwardEulerStep

// Implement BackwardEulerStep

void BackwardEulerStep(double x_now, double p_now, double *x_next, double *p_next, double h)
{
	// implicit method, so we must iterate to check convergence
	double x_1, p_1, x_2, p_2;
	double err, TOL;
	int iter, iter_max;

	iter_max = 100; // set max iteration to large value
	TOL = 10^(-10); // set tolerance to small value

	x_1 = x_now;
	p_1 = p_now;

	// iterate over to converge
	for (iter = 0; iter < iter_max; iter++)
	{
		OneStep(x_now, p_now, x_1, p_1, &x_2, &p_2, h);

		// calculate err
		err = fabs(p_2 - p_1) + fabs(x_2 - x_1); // not dimensionally correct but does job

		// prepare for next iteration step
		x_1 = x_2;
		p_1 = p_2;
	} // iter-loop

	if (err >= TOL) // iteration did not converge
	{
		printf("BackwardEulerStep iteration did not converge\n");
		exit(1); // exit
	}

	else // iteration did converge
	{
		// put x_2 and p_2 into x_next and p_next values 
		*x_next = x_2;
		*p_next = p_2;
	}

	return;
} // BackwardEulerStep

// Implement Leapfrog 1

void Leapfrog1Step(double x_now, double p_now, double *x_next, double *p_next, double h)
{
	// cannot use OneStep
	double x_step, p_step;

	// implement
	p_step = p_now + h*Force(x_now); // x_now already initialized as x_{1/2}
	x_step = x_now + h*Velocity(p_step);

	// store values in next pointers
	*x_next = x_step;
	*p_next = p_step;

	return;
} // Leapfrog 1

// Implement Leapfrog 2

void Leapfrog2Step(double x_now, double p_now, double *x_next, double *p_next, double h)
{
	double x_step, p_step;

	// implement
	x_step = x_now + h*Velocity(p_now);
	p_step = p_now + h*Force(x_step);

	// store
	*x_next = x_step;
	*p_next = p_step;

	return;
} // Leapfrog 2

// Evolve functions defined