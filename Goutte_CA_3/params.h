#ifndef PARAM_H
#define PARAM_H

// Pointer to a function that takes a vector argument
// This must be declared before being used below
typedef double (*FuncPt) (double *q, double t, int num_elems);

typedef struct neq_params
{
	int num_eq; // # of equations
	// same as # of dynamical variables

	double *q_i; // initial values for the dynamical variables
	double t_i; // initial time
	double t_f; // final time
	int it_max; // # of time steps
	double h; // time step size

	// this will become an array of functions
	// corresponding to the right hand side of dq_i/dt = f_i
	FuncPt *QVelos;

	// prob specific inputs (masses, moms of inertia, etc...)
	// for us, 3 principal I's
	double *I_prin;

} NeqParams; // structure element to be referenced from with . operator

NeqParams PARAM_DATA;

#endif