// This file is init.c 
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include "params.h" // to include struct PARAM_DATA
#include "init.h" 
#include "forces.h"

// Redefine functions from asst 1

void ReadInParams(char *input_file)
{
	double xr;
    int ir;
    FILE *input; // file pointer 

    input = fopen(input_file, "r"); // open the file for reading

    fscanf(input, "%lf", &xr); // read from the file one number at a time
    PARAM_DATA.mass = xr;  // mass

    fscanf(input, "%lf", &xr);  // initial position
    PARAM_DATA.x_i = xr; 

    fscanf(input, "%lf", &xr); // initial momentum
    PARAM_DATA.p_i = xr;

    fscanf(input, "%lf", &xr); // initial time
    PARAM_DATA.t_i = xr; 

    fscanf(input, "%lf", &xr); // final time
    PARAM_DATA.t_f = xr;  

    fscanf(input, "%d", &ir); // number of time intervals
    PARAM_DATA.it_max = ir;

    // Calculate h = (t_f - t_i)/it_max and store it
    xr = (PARAM_DATA.t_f - PARAM_DATA.t_i)/((double) PARAM_DATA.it_max);
    PARAM_DATA.h = xr;

    // algorithm choice
    fscanf(input, "%d", &ir);
    PARAM_DATA.choice = ir;

    fscanf(input, "%d", &ir);
    PARAM_DATA.num_eq = ir; 

    fscanf(input, "%lf", &xr);
    PARAM_DATA.k_spring = xr; 

    fclose(input); // always close when done

    return;
} // ReadInParams

void PrintParams(void) // only want to print, not print on file
{
	printf("Mass = %lf\n", PARAM_DATA.mass); // print mass

    printf("Initial position = %lf\n", PARAM_DATA.x_i); // initial pos

    printf("Initial momentum = %lf\n", PARAM_DATA.p_i); // init momt

    printf("Initial time = %lf\n", PARAM_DATA.t_i); // init time

    printf("Final time = %lf\n", PARAM_DATA.t_f); // final time

    printf("Number of time intervals = %d\n", PARAM_DATA.it_max); // no. of t ints

    printf("Time step size = %lf\n", PARAM_DATA.h); // time step size

    printf("choice = %d\n", PARAM_DATA.choice); // choice of solver

    printf("Number of diff. eqs = %d\n", PARAM_DATA.num_eq); // no. of diff. eqs

    printf("Spring constant = %lf\n", PARAM_DATA.k_spring); // spring constant

    return;
} // PrintParams

// Define new functions

void Initialize(double *x, double *p)
{
	double x_i, p_i, h;
	int choice;

	// get params from PARAM_DATA
	x_i = PARAM_DATA.x_i;
	p_i = PARAM_DATA.p_i;
	choice = PARAM_DATA.choice;

	// initialize parameters corresponding to solver

	if (choice == 3) // Leapfrog 1: x[0] = x(h/2)
	{
		// first element of momentum is initial momentum
		p[0] = p_i;

		// first element of position is x_{1/2} 
		// x(t_{1/2}) = x_i + 1/2*h*(dx/dt)
		// Finally: x_{1/2} = x_i + h/2*velocity(p_i)
		x[0] = x_i + h/2.0*Velocity(p_i);
	}

	if (choice == 4)
	{
		// first element of position is initial position
		x[0] = x_i;

		// first element of momentum is p_{1/2}
		// p_{1/2} = p(t_{1/2}) = p_i + 1/2*h*(dp/dt)
		// Finally: p_{1/2} = p_i + h/2*h*Force(x_i)
		p[0] = p_i + h/2.0*Force(x_i);
	}
	else
	{
		// all other methods have first element = initial data
		x[0] = x_i;
		p[0] = p_i;
	}

	return;
} // Initialize