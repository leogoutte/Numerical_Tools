#ifndef FORCES_H
#define FORCES_H

double QVelo0(double *q, double t, int num_elems);
double QVelo1(double *q, double t, int num_elems);
double QVelo2(double *q, double t, int num_elems);
double QVelo3(double *q, double t, int num_elems);

void Translate(double *q, double *theta_1, double *theta_2, double *p_1, double *p_2, 
		double *m_1, double *m_2, double *l_1, double *l_2);

double TotalEnergy(double *q);

#endif