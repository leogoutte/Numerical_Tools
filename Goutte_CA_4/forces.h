#ifndef FORCES_H
#define FORCES_H

double QVelo0(double *q, double t, int num_elems);
double QVelo1(double *q, double t, int num_elems);
double QVelo2(double *q, double t, int num_elems);
double QVelo3(double *q, double t, int num_elems);

void Translate(double *q, double *theta_1, double *theta_2, 
	double *p_1, double *p_2, double *mass1, double *mass2, 
	double *length1, double *length2);

double TotalEnergy(double *q);

#endif