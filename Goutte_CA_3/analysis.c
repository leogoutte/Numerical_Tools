// This file is analysis.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "params.h"
#include "analysis.h"

// implement KineticEnergy
double KineticEnergy(double *q)
{
	double I_1, I_2, I_3, q_1, q_2, q_3, K;

	I_1 = PARAM_DATA.I_prin[1];
	I_2 = PARAM_DATA.I_prin[2];
	I_3 = PARAM_DATA.I_prin[0];

	q_1 = q[1];
	q_2 = q[2];
	q_3 = q[0];

	K = (1.0/2.0)*(I_1*pow(q_1,2) + I_2*pow(q_2,2) + I_3*pow(q_3,2));

	return K;
}




