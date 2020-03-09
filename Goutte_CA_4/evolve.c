// evolve.c
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include "evolve.h" 
#include "forces.h" 
#include "params.h" 
#include "vector_mtx.h" 
#include "rk4.h" 

double GetAngle(double ang)
{
	double f,n;

	f = ang;
	n = floor(f/(2.0*PI));

	f -= 2.0*PI*n;

	return f;
} // GetAngle

void EvolveNeq(double *q)
{
	// declare variables
	double *q_next;
	double t_i, t_f, t_now, t_next, h;
	int num_eq;
	int count;
	double prec_goal, err;
	FuncPt *QVelos;
	FILE *output;

	// get times from PARAM_DATA
	t_i = PARAM_DATA.t_i;
	t_f = PARAM_DATA.t_f;

	// warn if t_i > t_f
	if (t_f < t_i)
	{
		fprintf(stderr, "Initial time is greater than final time\n");
		exit(1); // exit
	}

	// get necessary params
	num_eq = PARAM_DATA.num_eq;
	prec_goal = PARAM_DATA.prec_goal;
	QVelos = PARAM_DATA.QVelos;

	// allocate space to q_next
	q_next = vector_malloc(num_eq);

	// open file for writing
	output = fopen("result_201.dat", "w");

	// set t_now to initial time
	t_now = t_i;

	// initialize count
	count = 0;

	// record steps while t_now <= t_f
	do
	{
		RecordAStep(output, t_now, q, num_eq);

		h = PARAM_DATA.h;

		// use AdaptiveRK4Step while err > prec_goal
		do
		{
			t_next = t_now + h;

			err = AdaptiveRK4Step(q, q_next, QVelos, t_now, &t_next, h, num_eq);

			count += 3;

			h = EstimateNextH(err, prec_goal, h);

		} while (err > prec_goal);

		// set t_now to t_next since we have advanced an adaptive step
		t_now = t_next;

		// copy q_next onto q
		Vector_Copy(q_next, q, num_eq);

	} while (t_now <= t_f);

	// record the final step
	RecordAStep(output, t_now, q, num_eq);

	fclose(output);

	printf("count: %d\nThis is the amount of times we called our AdaptiveRK4Step function\n", count);

	return;
} // Evolve Neq

void RecordAStep(FILE *output, double t_now, double *q, int num_eq)
{
	// everything will be printed on the same row
	// print t_now
	fprintf(output, "%lf ", t_now);

	// record the angles and momenta
	double qs;
	for (int i = 0; i < num_eq; ++i)
	{
		// if angles, get modulo 2pi
		if ((i == 0) || (i == 1))
		{
			qs = GetAngle(q[i]);
		}
		else
		{
			qs = q[i];
		}
		fprintf(output, "%lf ", qs);
	} // i-loop

	// to record positions
	double l_1, l_2, theta_1, theta_2;
	double x_1, y_1, x_2, y_2;

	// translate into physical variables
	l_1 = PARAM_DATA.length1;
	l_2 = PARAM_DATA.length2;

	theta_1 = GetAngle(q[0]);
	theta_2 = GetAngle(q[1]);

	// calculate position of mass 1
	x_1 = l_1*sin(theta_1);
	y_1 = -l_1*cos(theta_1);

	// record
	fprintf(output, "%lf ", x_1);
	fprintf(output, "%lf ", y_1);

	// calculate position of mass 2
	x_2 = x_1 + l_2*sin(theta_2);
	y_2 = y_1 - l_2*cos(theta_2);

	// record
	fprintf(output, "%lf ", x_2);
	fprintf(output, "%lf ", y_2);

	// calculate total energy
	double energy;

	energy = TotalEnergy(q);

	// record energy
	fprintf(output, "%lf\n", energy);

	return;
} // RecordAStep