// This file is evolve.h
#ifndef EVOLVE_H
#define EVOLVE_H

void Evolve(double *x, double *p);

void AdvanceOneStep(double *x, double *p, int it_now, int choice);

// This is the workhorse
// It advances x_now and p_now by time step h to x_next and p_next 
// using x_in and p_in on the right hand side
void OneStep(double x_now, double p_now, double x_in, double p_in, double *x_next, double *p_next, double h);
// x_now, p_now, x_in, p_in, x_next, p_next, h

// declare all of the numerical solvers

void ForwardEulerStep(double x_now, double p_now, double *x_next, double *p_next, double h); 

void BackwardEulerStep(double x_now, double p_now, double *x_next, double *p_next, double h);

void Leapfrog1Step(double x_now, double p_now, double *x_next, double *p_next, double h); 

void Leapfrog2Step(double x_now, double p_now, double *x_next, double *p_next, double h);

// the other numerical solvers will be declared/defined later

// void VelocityVerletStep(double x_now, double p_now, double *x_next, double *p_next, double h);
// void PositionVerletStep(double x_now, double p_now, double *x_next, double *p_next, double h);

// void HeunStep(double x_now, double p_now, double *x_next, double *p_next, double h);
// void Heun3Step(double x_now, double p_now, double *x_next, double *p_next, double h);

// void RK4Step(double x_now, double p_now, double *x_next, double *p_next, double h);
// void RuthForestStep(double x_now, double p_now, double *x_next, double *p_next, double h);

// void PEFRLStep(double x_now, double p_now, double *x_next, double *p_next, double h);
// int OneStepWithErr(double x_now, double p_now, double *x_next, double *p_next, double *h_next, double h);
// void AdaptiveVerletStep(double x_now, double p_now, double *x_next, double *p_next, double h);

#endif