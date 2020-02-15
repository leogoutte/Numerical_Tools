// This file is analysis.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "params.h"
#include "analysis.h"

// implement KineticEnergy
double KineticEnergy(double *q)
{
	I_prin = PARAM_DATA.I_prin;
	I_1 = I_prin[1];
	I_2 = I_prin[2];
	I_3 = I_prin[0];

	q_1 = q[1];
	q_2 = q[2];
	q_3 = q[0];

	K = (1/2)*(I_1*pow(q_1,2) + I_2*pow(q_2,2) + I_3*pow(q_3,2));

	return K;
}

// Implement write results

void WriteResults(double *x, double *p)
{
	int it, it_max;
	FILE *output; // pointer to a file
	double t, h, x_now, p_now;

	it_max = PARAM_DATA.it_max; // get values from struct
	h = PARAM_DATA.h;

	output = fopen("Results.dat", "w"); // open for writing

	for (it=0; it<it_max; it++)
	{
		t = h*it;

		// get x and p for time h*it
		GetXP(x, p, &x_now, &p_now, it);

		fprintf(output, "%lf %lf %lf\n", t, x_now, p_now); // write values onto file
	} // it-loop

	fclose(output);

	return;
}

// Implement getxp

void GetXP(double *x, double *p, double *x_now, double *p_now, int it)
{
	int choice, it_max;
	double h;

	// fetch values
	choice = PARAM_DATA.choice;
	it_max = PARAM_DATA.it_max;
	h = PARAM_DATA.h;

	if (choice == 3) // Leapfrog 1, x[0] = x(h/2)
	{
		*p_now = p[it]; // fine

		// for position, go back a half step

		if (it == 0)
		{
			*x_now = PARAM_DATA.x_i; // initial x_i is just from param_data
		}
		else
		{
			*x_now = (x[it-1]+x[it])/2.0; // take average
		}
	} // choice = 3
	else if (choice ==4) // leapfrog 2, p[0] = p(h/2)
	{
		*x_now = x[it]; // fine

		// for momentum, go back a half step

		if (it == 0)
		{
			*p_now = PARAM_DATA.p_i;
		}
		else
		{
			*p_now = (p[it-1]+p[it])/2.0; // take average
		}
	} // choice = 4
	else
	{
		*x_now = x[it]; // just take value at t = h*it
		*p_now = p[it];
	} // other

	return;
} // getXP




