#include <stdlib.h>
#include <stdio.h>
#include "params.h"

// define the functions

// ReadInParams
void ReadInParams(char *input_file)
{
    double xr;
    int ir;
    FILE *input; // file pointer 

    input = fopen(input_file, "r"); // open the file for reading

    fscanf(input, "%lf", &xr); // read from the file one number at a time
    PARAM_DATA.mass = xr; 

    fscanf(input, "%lf", &xr); 
    PARAM_DATA.x_i = xr; 

    fscanf(input, "%lf", &xr); 
    PARAM_DATA.p_i = xr;

    fscanf(input, "%lf", &xr); 
    PARAM_DATA.t_i = xr; 

    fscanf(input, "%lf", &xr);
    PARAM_DATA.t_f = xr;  

    fscanf(input, "%d", &ir);
    PARAM_DATA.it_max = ir;

    // Calculate h = (t_f - t_i)/it_max and store it
    xr = (PARAM_DATA.t_f - PARAM_DATA.t_i)/((double) PARAM_DATA.it_max);
    PARAM_DATA.h = xr;

    fscanf(input, "%d", &ir);
    PARAM_DATA.num_eq = ir; 

    fscanf(input, "%lf", &xr);
    PARAM_DATA.k_spring = xr; 

    fclose(input); // always close when done
    return;
} // ReadInParams

// PrintParams
void PrintParams(void)
{
    FILE *output; // pointer to a file
    output = fopen("InitParams.dat", "w");
    {
        fprintf(output, "Mass %lf\n", PARAM_DATA.mass); // write params onto
        fprintf(output, "Initial_position %lf\n", PARAM_DATA.x_i); // .dat output file
        fprintf(output, "Initial_momentum %lf\n", PARAM_DATA.p_i);
        fprintf(output, "Initial_time %lf\n", PARAM_DATA.t_i);
        fprintf(output, "Final_time %lf\n", PARAM_DATA.t_f);
        fprintf(output, "Num_time_intervals %d\n", PARAM_DATA.it_max);
        fprintf(output, "Time_step_size %lf\n", PARAM_DATA.h);
        fprintf(output, "Num_diff_eqs %d\n", PARAM_DATA.num_eq);
        fprintf(output, "Spring_constant %lf\n", PARAM_DATA.k_spring);
    } // done writing
    fclose(output);

    // print each parameter onto terminal to check
    printf("Mass = %lf\n", PARAM_DATA.mass); 
    printf("Initial position = %lf\n", PARAM_DATA.x_i);
    printf("Initial momentum = %lf\n", PARAM_DATA.p_i);
    printf("Initial time = %lf\n", PARAM_DATA.t_i);
    printf("Final time = %lf\n", PARAM_DATA.t_f);
    printf("Number of time intervals = %d\n", PARAM_DATA.it_max);
    printf("Time step size = %lf\n", PARAM_DATA.h);
    printf("Number of diff. eqs = %d\n", PARAM_DATA.num_eq);
    printf("Spring constant = %lf\n", PARAM_DATA.k_spring);
}// PrintParams

