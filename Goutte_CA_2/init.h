// This file is init.h
#ifndef INIT_H
#define INIT_H

#include "params.h"

// same funcs
void ReadInParams(char *input_file); 
void PrintParams(void);

// new function to initialize x and p
void Initialize(double *x, double *p);

#endif