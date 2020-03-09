#ifndef RK4_H
#define RK4_H

void RK4Step(double *q, double *q_next, FuncPt *QVelos, double t_now, 
	double h, int num_eq);

void OneStepNeq(double *q_now, double *q_in, double *q_next, FuncPt *QVelos, 
	double t_in, double h, int num_eq);

double AdaptiveRK4Step(double *q, double *q_next, FuncPt *QVelos, double t_now,
	double *t_next, double h, int num_eq);

double EstimateError(double *q_full, double *q_next, double t_now, 
	double h, int num_eq);

double EstimateNextH(double err, double err0, double h);

#endif