#ifndef PARAMS_H // make sure that each header file
#define PARAMS_H // is included only once

typedef struct params
{
 double mass; // mass
 double x_i; // initial position
 double p_i; // initial momentum
 double t_i; // initial time
 double t_f; // final time
 int it_max; // number of time intervals
 double h; // time step size
 int num_eq; // number of first order diff equations

 // problem specific parameters
 double k_spring; // for SHO 
} Params; 

Params PARAM_DATA; // so that it can be shared globally whenever params.h 
                   // is included in function declarations
void ReadInParams(char *input_file); 
void PrintParams(void); 
#endif // make sure that each header file is included only once