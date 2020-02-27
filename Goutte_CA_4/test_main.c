#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vector_mtx.h"

int main(int argc, char const *argv[])
{
	double *a, *b;
	a = vector_malloc(3);
	b = vector_malloc(3);

	double check;
	check = Vector_Distance(a, b, 3);

	printf("This should be zero: %lf\n", check);
	return 0;
}