#ifndef PARAM_H
#define PARAM_H

// need numerical value of pi
#define PI 3.1415926535897932385

// pointer to a function that takes a vector argument
typedef double (*FuncPt)(double *q, double t, int num_elems);

typedef struct euler_params
{
	// initial values
	double *q_i;
	double t_i;
	double t_f;

	// this will become an array of functions
	FuncPt *QVelos;

	// problem specific quantities
	double h;
	int num_eq;

	double prec_goal; // to control precision of calculations

	// two masses in kg
	double mass1;
	double mass2;

	// two lengths in m
	double length1;
	double length2;
} NeqParams;

NeqParams PARAM_DATA;
#endif