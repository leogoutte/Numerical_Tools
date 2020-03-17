#ifndef NUM_INTEG_H
#define NUM_INTEG_H

// given (f_0, ... f_nmax)
// this calculates the sub-integral b/w x_down = h*down and x_up = h*up
// where down and up are the integer indices between 0 and nmax
double NumIntegrate(double *f, double h, int down, int up, int nmax);

// This calculates integral dx f(x) from x_down to x_up
// using num_interval number of intervals
double NumIntegrateV(double (*func)(double), double x_down, double x_up, int num_intervals);

// This calculates int dx f(x) using adaptive Simpson method
double AdaptiveIntegrate(double (*func)(double), double down, double h, double *f_prev, double ans_prev, double tol, int *count);

// This is the wrapper for AdaptiveIntegrate
double Integrate(double (*integrand)(double), double x_down, double x_up, double Tol, int *count, int limit);

#endif