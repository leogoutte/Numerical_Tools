// This file is forces.c
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include "params.h" 
#include "forces.h"

// forces & velocities

// this is simply v = p/m 
double Velocity(double p) {
 double v, mass; 
 mass = PARAM_DATA.mass; // get mass from PARAM_DATA
 v = p/mass; // calculate v = p/mass
 return v;
}// Velocity

double Force(double x)
{
 double f, k;
 k = PARAM_DATA.k_spring; // get k from PARAM_DATA
 f = -k*x; // Calculate f = -k*x
 return f;
}// Force