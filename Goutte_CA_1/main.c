#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h" 
#include "params.h"

int main(int argc, char **argv) // to specify the input file
{
// argc is the number of words you used when you executed this program 
// argv contains those words.
// for instance, if your executable is named my_exec and
// you run your program with
// my_exec input ouput
// then argc = 3 and
// argv[0] = my_exect, argv[1] = input, argv[2] = output 
// This particular program should run as
// my_exect input
// where input is the name of your input parameter file

 char *input_file; // Name of the input file
                // This is a pointer to the character vector
                // that contains the name

 input_file = argv[1]; // argv[1] is your input file
 ReadInParams(input_file); 
 PrintParams();
 return 0;
}// main