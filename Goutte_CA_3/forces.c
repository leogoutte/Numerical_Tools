// forces.c
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include "params.h" 
#include "forces.h"

// forces and velocities
// This is problem-specific
// For our problem (Euler Equation), implement the right hand side of 
// dq_1/dt = ( (I_2 - I_3)/I_1 ) q_2 q_3
// dq_2/dt = ( (I_3 - I_1)/I_2 ) q_3 q_1
// dq_3/dt = ( (I_1 - I_2)/I_3 ) q_1 q_2

// Take q[0] to be q_3 and I_prin[0] to be I_3

double QVelo0(double *q, double t, int num_elems) // dq_3/dt
{
	double f;
	double I_1, I_2, I_3;

	I_1 = PARAM_DATA.I_prin[1];
	I_2 = PARAM_DATA.I_prin[2];
	I_3 = PARAM_DATA.I_prin[0];

	f = ((I_1 - I_2)/I_3)*(q[1]*q[2]);

	return f;

} //QVelo0

double QVelo1(double *q, double t, int num_elems) // dq_1/dt
{
	double f;
	double I_1, I_2, I_3;

	I_1 = PARAM_DATA.I_prin[1];
	I_2 = PARAM_DATA.I_prin[2];
	I_3 = PARAM_DATA.I_prin[0];

	f = ((I_2 - I_3)/I_1)*(q[2]*q[0]);
	
	return f;

} //QVelo1

double QVelo2(double *q, double t, int num_elems) // dq_2/dt
{
	double f;
	double I_1, I_2, I_3;

	I_1 = PARAM_DATA.I_prin[1];
	I_2 = PARAM_DATA.I_prin[2];
	I_3 = PARAM_DATA.I_prin[0];

	f = ((I_3 - I_1)/I_2)*(q[0]*q[1]);

	return f;

} //QVelo2