#ifndef EVOLVE_H
#define EVOLVE_H

double GetAngle(double ang);

void RecordAStep(FILE *output, double t_now, double *q, int num_eq);

void EvolveNeq(double *q);

#endif