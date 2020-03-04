#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vector_mtx.h"

int main(int argc, char const *argv[])
{
	double *a, *b;
	a = vector_malloc(2);
	b = vector_malloc(2);

	double check;
	a[0] = 1.;
	a[1] = 1.;
	a[2] = 3.;
	a[28] = 3.;
	printf("%lf\n", a[23]);
	printf("[%lf]\n", a[0]);
	printf("[%lf]\n", a[1]);

	b[0] = 4.;
	b[1] = 5.;

	printf("[%lf]\n", b[0]);
	printf("[%lf]\n", b[1]);

	check = Vector_Distance(a, b, 2);

	printf("This should be five: %lf\n", check);
	return 0;
}