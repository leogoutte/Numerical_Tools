// main.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "num_integ.h"

// Kepler function (integrand)
double Kepler(double r);

// Make sure that the main in num_integ.c is commented out

int main()
{
	FILE *output;
	// declare variables
	double K, m, phi, pphi, ene;
	double r_up, r_down, r, dr;
	double x, y;
	double tol;
	int nmax, limit, count;

	// set params
	K = 1.0/137.0;
	m = 0.511e+6;
	pphi = 2.0;
	ene = -1.0;

	// implement r_up
	r_up = K + pow(K*K - 2*fabs(ene)*pphi*pphi/m,0.5);
	r_up /= 2*fabs(ene);

	// implement r_down
	r_down = K - pow(K*K - 2*fabs(ene)*pphi*pphi/m,0.5);
	r_down /= 2*fabs(ene);

	// print for reference
	printf("r_up = %lf\n", r_up);
	printf("r_down = %lf\n", r_down);

	// set tol, limit, nmax
	tol = 1e-10;
	limit = 10000;
	nmax = 100;

	// open output file
	output = fopen("kepler.dat", "w");

	// dr
	dr = r_up - r_down;
	dr /= nmax;

	// calculate the kepler orbit
	for (int n = 0; n <= nmax; n++)
	{
		// set r to current step
		r = r_down + n*dr;

		// initialize count
		count = 0;

		// integrate from lower bound to current step
		phi = Integrate(Kepler, r_down, r, tol, &count, limit);

		// get x and y to plot
		x = r * cos(phi);
		y = r * sin(phi);

		// put the in output file
		fprintf(output, "%lf %lf\n", x, y);
	} // n-loop

	fclose(output);

	return 0;
} // main

// Implement Kepler integrand
double Kepler(double r)
{
	double f, K, m, pphi, ene, arg;

	// set params
	K = 1.0/137.0;
	m = 0.511e+6;
	pphi = 2.0;
	ene = -1.0;

	// this is dr/dt
	arg = pow(2/m * (ene - pphi*pphi/(2*m*r*r) + K/r) + 1e-16, 0.5); // ad a little to make sure it doesn't blow up

	// this is d\phi/dr
	f = pphi/(m*r*r);
	f /= arg;

	return f;
} // Kepler