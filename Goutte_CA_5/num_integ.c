// num_integ.c
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "num_integ.h"

// test-integrand
double test_func(double x);

// To test numerical integration routines
int TestNumInteg();

// This function implements the equal-interval formulas for numerical integral 
// vector f runs from f[0] to f[nmax]
// down and up are integers between 0 and nmax,
// h is the interval between f[n] and f[n+1]



double NumIntegrate(double *f, double h, int down, int up, int nmax)
{
	// declare variables
	double sum;

	if (up > nmax || down > nmax || up < 0 || down < 0)
	{
		fprintf(stderr, "Indices are out of bounds for axis of size %d\n", nmax);
		exit(1);
	} // if-loop

	if (down > up) // integral will get a minus sign
	{
		int tmp;

		tmp = up;
		up = down;
		down = tmp;

		h *= -1.0; // does not change h outside this function
	} // if-loop

	// bounds are the same
	if (up == down)
	{
		return 0.0;
	}

	// single interval
	else if (up == down + 1)
	{
		sum = f[down] + f[down + 1];
		sum *= h/2.0;
	} // single interval

	// two intervals
	else if (up == down + 2)
	{
		sum = f[down] + 4.0 * f[down + 1] + f[down + 2];
		sum *= h/3.0;
	} // two intervals

	// three intervals
	else if (up == down + 3)
	{
		sum = f[down] + 3 * f[down + 1] + 3 * f[down + 2] + f[down + 3];
		sum *= 3.0;
		sum *= h/8.0;
	} // three intervals

	// four intervals
	else if (up == down + 4)
	{
		sum = 14 * f[down] + 64 * f[down + 1] + 24 * f[down + 2] + 64 * f[down + 3] + 14 * f[down + 4];
		sum *= h/45.0;
	} // four intervals

	// five intervals
	else if (up == down + 5)
	{
		sum = 19 * f[down] + 75 * f[down + 1] + 50 * f[down + 2] + 50 * f[down + 3] + 75 * f[down + 4] + 19 * f[down + 5];
		sum *= 5.0 * h/288.0;
	} // five intervals

	// more than 6 intervals (7 points)
	else
	{
		int num_ints, upper_bound;
		num_ints = up - down;
		upper_bound = num_ints - 3;

		// first part of sum
		sum = 3.0/8.0 * f[down] + 7.0/6.0 * f[down + 1] + 23.0/24.0 * f[down + 2];

		// sum part
		for (int i = 3; i <= upper_bound; i++)
		{
			sum += f[down + i];
		} // i-loop

		// last part of sum
		sum += 23.0/24.0 * f[down + (num_ints - 2)] + 7.0/6.0 * f[down + (num_ints - 1)] + 3.0/8.0 * f[down + num_ints];

		sum *= h;

	} // more than 7 points

	return sum;
} // NumIntegrate

// This is a wrapper for NumIntegrate.
// This function takes in the integrand func, the lower bound x_down,
// the upper bound x_up, and the number of intervals
// to evaluate the integral int_{x_down}^{x_up} dx func(x)

double NumIntegrateV(double (*func)(double), double x_down, double x_up, int num_intervals)
{
	// declare variables
	double *vf;
	double h;
	double x;
	double f;

	// allocate memory to vf
	vf = (double*)malloc(sizeof(double)*(num_intervals + 1));

	// calculate h
	h = (x_up - x_down);
	h /= num_intervals;

	// populate vf
	for (int n = 0; n <= num_intervals; n++)
	{
		x = x_down + n * h;
		vf[n] = func(x);
	} // n-loop

	// Use NumIntegrate
	f = NumIntegrate(vf, h, 0, num_intervals, num_intervals);

	// free vf
	free(vf);

	return f;
} // NumIntegrateV

// Adaptive numerical integration function
// func is the integrand, x_down is the lower limit of the integral 
// h = (x_up - x_down)/2 to begin with

// f_prev is the previously evaluated function array
// ans_prev is the previous estimate of the integral 
// tol is the tolerance level and
// count counts the number of function calls
// Here is a visualization of how the arrays are organized:
//
//       L           R
// 0    h/2    h   3h/2   2h
// I-----I-----I-----I-----I
// 0 	 	   1 	 	   2 <- f_prev index
// 0     1     2             <- f_l index
// 			   0     1     2 <-f_rindex

double AdaptiveIntegrate(double (*func)(double), double x_down, double h, double *f_prev, double ans_prev, double tol, int *count)
{
	// Prepare left and right half estimates
	double fl[3], fr[3];

	// simpson rule weights
	double w[3] = {1.0/3.0, 4.0/3.0, 1.0/3.0};

	// declare variables
	double h_half;
	double ans_l, ans_r, ans_now;
	double err;

	// calculate half of h
	h_half = h/2.0;

	// prepare fl and fr
	fl[0] = f_prev[0];
	fl[2] = f_prev[1];
	fl[1] = func(x_down + h_half);

	fr[0] = f_prev[1];
	fr[2] = f_prev[2];
	fr[1] = func(x_down + 3.0 * h_half);

	// add 2 to count
	*count += 2;

	// evaluate left interval estimate ans_l
	ans_l = 0.0;
	for (int i = 0; i < 3; i++)
	{
		ans_l += w[i] * fl[i];
	} // i-loop
	ans_l *= h;

	// ditto with right
	ans_r = 0.0;
	for (int i = 0; i < 3; i++)
	{
		ans_r += w[i] * fr[i];
	} // i-loop
	ans_r *= h;	

	// add them up
	ans_now = ans_l + ans_r;

	// estimate the error
	err = (ans_now - ans_prev)/15.0;

	// if error is too large, divide the integrals and try again
	if (fabs(err) > tol)
	{
		ans_l = AdaptiveIntegrate(func, x_down, h_half, fl, ans_l, tol, count);
		ans_r = AdaptiveIntegrate(func, x_down + h, h_half, fr, ans_r, tol, count);

		ans_now = ans_l + ans_r;
	} // err > tol

	// else, correct and return
	else
	{
		ans_now += err;
	}

	return ans_now;
} // AdaptiveIntegrate

// The wrapper for the adaptive numerical integration
// integrand is the integrand
// x_down is the lower limit of the integral
// x_up is the upper limit
// count is the number of function calls
// limit is the maximum allowed number of function calls

double Integrate(double (*integrand)(double), double x_down, double x_up, double tol, int *count, int limit)
{
	// declare variables
	// simpson weights
	double w[3] = {1.0/3.0, 4.0/3.0, 1.0/3.0};
	// prep for adaptive simpson integral
	double f_prev[3];
	// others
	double h;
	double f, x;
	double ans_prev;

	// calculate h
	h = (x_up - x_down)/2.0;

	// calculate first estimate using simpson's rule
	ans_prev = 0.0;
	for (int i = 0; i < 3; i++)
	{
		// get x to be evaluated at
		x = x_down + i*h;
		// store in f_prev
		f_prev[i] = integrand(x);
		// add to ans_prev
		ans_prev += w[i] * f_prev[i];
		ans_prev *= h; 
	} // i-loop

	// function was called 3 times
	*count += 3;

	// calculate the integral
	f = AdaptiveIntegrate(integrand, x_down, h, f_prev, ans_prev, tol, count);

	if (*count > limit)
	{
		fprintf(stderr, "Count limit has been exceeded. Integral may not have been evaluated to the set tolerance level\n");
	}

	return f;
} // Integrate

/*
double test_func(double x)
{
	double f, R, a;

	f = sin(1.0/x);

	return f;
} // test_func

int TestNumInteg()
{
	double f_prev[3];
	double w[3] = {1.0/3.0, 4.0/3.0, 1.0/3.0};
	double (*integrand)(double); // function pointer for the integrand
	FILE *output;
	double x_down, x_up;
	int num_intervals;
	double f, g, err;
	double tol;
	int limit, count;

	integrand = test_func;

	x_down = 0.001;
	x_up = 10.0;

	g = 2.726201989096137; // real value of integral

	// open file for writing
	output = fopen("num_integ_test.dat", "w");

	// set num_intervals = 100
	num_intervals = 100;
	f = NumIntegrateV(integrand, x_down, x_up, num_intervals);

	// print onto output
	fprintf(output, "Value of integral with %d intervals using num_intervals method:\n%lf,%d\n", 
		num_intervals, f, num_intervals);
	err = fabs(f - g);
	fprintf(output, "Relative error between integral and real value:\n%lf\n", err);

	// set num_intervals = 1000
	num_intervals = 1000;
	f = NumIntegrateV(integrand, x_down, x_up, num_intervals);

	// print onto output
	fprintf(output, "Value of integral with %d intervals using num_intervals method:\n%lf,%d\n", 
		num_intervals, f, num_intervals);
	err = fabs(f - g);
	fprintf(output, "Relative error between integral and real value:\n%lf\n", err);

	// Set tol = 1.0e-10
	tol = 1.0e-10;
	limit = 10000;
	count = 0;

	// calculate integral
	f = Integrate(integrand, x_down, x_up, tol, &count, limit);

	// print onto output
	fprintf(output, "Value of integral using adaptive simpson method with counts:\n%lf,%d\n", 
		f, count);
	err = fabs(f - g);
	fprintf(output, "Relative error between integral and real value:\n%lf\n", err);

	// Set num_intervals = count
	num_intervals = count;

	// integrate using num_ints method
	f = NumIntegrateV(integrand, x_down, x_up, num_intervals);

	fprintf(output, "Value of integral with %d intervals using num_intervals method:\n%lf,%d\n", 
		num_intervals, f, num_intervals);
	err = fabs(f - g);
	fprintf(output, "Relative error between integral and real value:\n%lf\n", err);

	fclose(output);

	return 1;
} // TestNumInteg

// For testing
int main()
{
	TestNumInteg();
	return 1;
} // test main
*/